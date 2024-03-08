#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
const int WIDTH = 80;
const int HEIGHT = 20;
int tailX[100], tailY[100], nTail;
int x, y, dotX, dotY, score;

enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup()
{
    gameOver = false;
    dir = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;
    dotX = rand() % WIDTH;
    dotY = rand() % HEIGHT;
    score = 0;
}

void Draw()
{
    system("cls");
    for (size_t i = 0; i < WIDTH; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)
                std::cout << "#";
            else if (i == y && j == x)
                std::cout << "O";
            else if (i == dotY && j == dotX)
                std::cout << "X";
            else
            {
                bool print = false;
                for (size_t k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }

                if (!print)
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    for (size_t i = 0; i < WIDTH; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (size_t i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
        gameOver = true;

    for (size_t i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == dotX && y == dotY)
    {
        score += 10;
        dotX = rand() % WIDTH;
        dotY = rand() % HEIGHT;
        nTail++;
    }
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }

    return 0;
}
