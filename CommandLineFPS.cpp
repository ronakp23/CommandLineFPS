#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
using namespace std;

#include <stdio.h>
#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 40;
int nMapWidth = 16;
int nMapHeight = 16;

float fPlayerX = 14.7f;
float fPlayerY = 5.09f;
float fPlayerA = 0.0f;
float fFOV = 3.14159f / 4.0f;
float fDepth = 16.0f;
float fSpeed = 5.0f;

int main() {
    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

    wstring map;
	map += L"#########.......";
	map += L"#...............";
	map += L"#.......########";
	map += L"#..............#";
	map += L"#....###.......#";
	map += L"###............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#......####..###";
	map += L"#......#.......#";
	map += L"#......#.......#";
	map += L"#..............#";
	map += L"####...#########";
	map += L"#..............#";
	map += L"################";

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();


    while(1) {
        tp2 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;
        
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            fPlayerA += (fSpeed * 0.75f) * fElapsedTime;

        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
            fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
            if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
                fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
                fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
            }
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
            fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
            fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
            if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
                fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
                fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
            }
        }
        

    }


    return 0;
}