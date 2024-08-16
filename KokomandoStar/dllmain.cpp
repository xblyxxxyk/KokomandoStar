#include "pch.h"
#include <windows.h>
#include <iostream>
#include <vector>
#define IsKeyDown(Key) (GetAsyncKeyState(Key) & 0x8000)
DWORD GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets)
{

    DWORD addr = ptr;
    for (int i = 0; i < offsets.size(); ++i) {
        addr = *(DWORD*)addr;
        addr += offsets[i];
    }
    return addr;
}
// offsets
int KokomandoWorld = 0xD5CDC;
int MagnumMovement = 0xD68C4;
int MagnumVehicle = 0xD5514;
int Zycie = 0x16C4;
int Zdrowie = 0x16C0;
int Ziarno = 0x16BC;
int BronZapalkowaAmunicja = 0x170C;
int BronWodnaAmunicja = 0x1708;
int JajkowaBazookaAmunicja = 0x1718;
int BronPinezkowaAmunicja = 0x1714;
int BronNiebieskoKulkowaAmunicja = 0x1710;
int Latanie = 0x23F4;
int WartoscX = 0x23F8;
int WartoscZ = 0x23F0;
int CarLapPTR1 = 0x1384;
int CarLapPTR2 = 0x2DC;
int GrabLevelBase = 0xD8ED0;
int GrabPTR1 = 0x8;
int GrabPTR2 = 0x5350;

HANDLE hThread = NULL; // Thread handle
DWORD modulebase = (DWORD)GetModuleHandle(L"Kokomando.exe");

int* currentlevel = (int*)GetPointerAddress(modulebase + GrabLevelBase, { static_cast<unsigned long>(GrabPTR1), static_cast<unsigned long>(GrabPTR2) });
int lvlptr = 0x0;
int lvlgun = 0x0;


// lvloffsets
int l1 = 0x8;
int l2 = 0x10;
int l11 = 0xC;


//cfg
int Speedhack = 50;
int FlySpeed = 300;
int HealthCount = 99;
int AmmoCount = 1000;
int LivesCount = 99;
int ZiarnoCount = 50;
int LapCount = 10;

void LevelCheck() {
    switch (*currentlevel) {
    case 1: //MAIN MENU
        std::cout << "Funkcja nie zadziala w menu glownym!";
        break;
    case 347: //LEVEL 1
        lvlptr = l1;
        lvlgun = BronZapalkowaAmunicja;
        break;
    case 610: //LEVEL 2
        lvlptr = l2;
        lvlgun = JajkowaBazookaAmunicja;
        break;
    case 401: //LEVEL 3
        lvlptr = l1;
        lvlgun = BronNiebieskoKulkowaAmunicja;
        break;
    case 370: //LEVEL 4
        lvlptr = l1;
        lvlgun = BronNiebieskoKulkowaAmunicja;
        break;
    case 387: //LEVEL 5
        lvlptr = l1;
        lvlgun = BronNiebieskoKulkowaAmunicja;
        break;
    case 319: //LEVEL 6
        lvlptr = l1;
        lvlgun = JajkowaBazookaAmunicja;
        break;
    case 381: //LEVEL 7
        lvlptr = l1;
        lvlgun = BronZapalkowaAmunicja;
        break;
    case 632: //LEVEL 8
        lvlptr = l1;
        lvlgun = JajkowaBazookaAmunicja;
        break;
    case 328: //LEVEL 9
        lvlptr = l1;
        lvlgun = BronPinezkowaAmunicja;
        break;
    case 242: //LEVEL 10
        lvlptr = l1;
        lvlgun = BronNiebieskoKulkowaAmunicja;
        break;
    case 374: //LEVEL 11
        lvlptr = l11;
        lvlgun = BronNiebieskoKulkowaAmunicja;
        break;
    case 117: //LEVEL 12
        lvlptr = l1;
        lvlgun = BronZapalkowaAmunicja;
        break;
    case 193: //LEVEL 13
        lvlptr = l1;
        lvlgun = JajkowaBazookaAmunicja;
        break;
    case 696: //LEVEL 14
        lvlptr = l1;
        break;
    case 346: //LEVEL 15
        lvlptr = l1;
        lvlgun = JajkowaBazookaAmunicja;
        break;
    case 266: //LEVEL 16
        lvlptr = l1;
        lvlgun = BronWodnaAmunicja;
        break;
    case 302: //LEVEL 17 && 18  Level 17 will not have "INFINITE" ammo, but the ammo will still not end due to water gun being the worst gun in the game, as such it doesnt change to a different one after ammo ends.
        lvlptr = l1;
        lvlgun = JajkowaBazookaAmunicja;
        break;
    }
}
// Thread function
DWORD WINAPI Kokomando(LPVOID lpParam)
{
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    std::cout << "Kokomando Cheat | Made by blyscyk" << std::endl;


    if (!modulebase) {
        std::cout << "Modul glowny nie znaleziony! Prosze o zainjectowanie do Kokomando.";
        Sleep(10000);
        abort();
    }
    std::cout << "[F] Latanie (Trzymaj Przycisk)" << std::endl;
    std::cout << "[F1] 1000 Amunicji" << std::endl;
    std::cout << "[F2] 99 Zyc" << std::endl;
    std::cout << "[F3] 99 Zdrowia" << std::endl;
    std::cout << "[F4] 50 Dukatow (+1 Zycie po zebraniu nastepnego Dukata)" << std::endl;
    std::cout << "[F5] Natychmiast Wygraj Wyscig (Poziom 14)" << std::endl;
    std::cout << "[NUMPAD 2,4,6,8] Szybkosc X-, Z-, X+, Z+" << std::endl;
    std::cout << "[F12] Pokaz Obecny Poziom" << std::endl;


    while (!IsKeyDown(VK_END))
    {


        if (IsKeyDown(VK_F1))
        {
            LevelCheck();
            int* ammo = (int*)GetPointerAddress(modulebase + KokomandoWorld, { static_cast<unsigned long>(lvlptr), static_cast<unsigned long>(lvlgun) });
            *ammo = AmmoCount;
        }

        if (IsKeyDown(VK_F2))
        {
            LevelCheck();
            int* lives = (int*)GetPointerAddress(modulebase + KokomandoWorld, { static_cast<unsigned long>(lvlptr), static_cast<unsigned long>(Zycie) });
            *lives = LivesCount;
        }

        if (IsKeyDown(VK_F3))
        {
            LevelCheck();
            int* health = (int*)GetPointerAddress(modulebase + KokomandoWorld, { static_cast<unsigned long>(lvlptr), static_cast<unsigned long>(Zdrowie) });
            *health = HealthCount;
        }

        if (IsKeyDown(VK_F4))
        {
            LevelCheck();
            int* ziarno = (int*)GetPointerAddress(modulebase + KokomandoWorld, { static_cast<unsigned long>(lvlptr), static_cast<unsigned long>(Ziarno) });
            *ziarno = ZiarnoCount;
        }

        if (IsKeyDown(VK_F5))
        {
            LevelCheck();
            int* okrazenie = (int*)GetPointerAddress(modulebase + MagnumVehicle, { static_cast<unsigned long>(CarLapPTR1), static_cast<unsigned long>(CarLapPTR2) });
            *okrazenie = LapCount;
        }

        if (IsKeyDown(0x46))
        {
            LevelCheck();
            float* ypos = (float*)GetPointerAddress(modulebase + MagnumMovement, { static_cast<unsigned long>(Latanie) });
            *ypos += FlySpeed;
        }

        if (IsKeyDown(VK_NUMPAD2)) // X-
        {
            float* xpos = (float*)GetPointerAddress(modulebase + MagnumMovement, { static_cast<unsigned long>(WartoscX) });
            *xpos += -Speedhack;
        }

        if (IsKeyDown(VK_NUMPAD4)) // Z-
        {
            float* zpos = (float*)GetPointerAddress(modulebase + MagnumMovement, { static_cast<unsigned long>(WartoscZ) });
            *zpos += -Speedhack;
        }

        if (IsKeyDown(VK_NUMPAD6)) // X+
        {
            float* xpos = (float*)GetPointerAddress(modulebase + MagnumMovement, { static_cast<unsigned long>(WartoscX) });
            *xpos += Speedhack;
        }

        if (IsKeyDown(VK_NUMPAD8)) // Z+
        {
            float* zpos = (float*)GetPointerAddress(modulebase + MagnumMovement, { static_cast<unsigned long>(WartoscZ) });
            *zpos += Speedhack;
        }

        if (IsKeyDown(VK_F12)) {
            switch (*currentlevel) {
            case 1: //MAIN MENU
                std::cout << "Funkcja nie zadziala w menu glownym!";
                break;
            case 347: //LEVEL 1
                std::cout << "Poziom 1" << std::endl;
                break;
            case 610: //LEVEL 2
                std::cout << "Poziom 2" << std::endl;
                break;
            case 401: //LEVEL 3
                std::cout << "Poziom 3" << std::endl;
                break;
            case 370: //LEVEL 4
                std::cout << "Poziom 4" << std::endl;
                break;
            case 387: //LEVEL 5
                std::cout << "Poziom 5" << std::endl;
                break;
            case 319: //LEVEL 6
                std::cout << "Poziom 6" << std::endl;
                break;
            case 381: //LEVEL 7
                std::cout << "Poziom 7" << std::endl;
                break;
            case 632: //LEVEL 8
                std::cout << "Poziom 8" << std::endl;
                break;
            case 328: //LEVEL 9
                std::cout << "Poziom 9" << std::endl;
                break;
            case 242: //LEVEL 10
                std::cout << "Poziom 10" << std::endl;
                break;
            case 374: //LEVEL 11
                std::cout << "Poziom 11" << std::endl;
                break;
            case 117: //LEVEL 12
                std::cout << "Poziom 12" << std::endl;
                break;
            case 193: //LEVEL 13
                std::cout << "Poziom 13" << std::endl;
                break;
            case 696: //LEVEL 14
                std::cout << "Poziom 14" << std::endl;
                break;
            case 346: //LEVEL 15
                std::cout << "Poziom 15" << std::endl;
                break;
            case 266: //LEVEL 16
                std::cout << "Poziom 16" << std::endl;
                break;
            case 302: //LEVEL 17 && 18  Level 17 will not have "INFINITE" ammo, but the ammo will still not end due to water gun being the worst gun in the game, as such it doesnt change to a different one after ammo ends.
                std::cout << "Poziom 17/18" << std::endl;
                break;
            }
            Sleep(500);
        }

        Sleep(10);
    }

    FreeConsole();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hThread = CreateThread(NULL, 0, Kokomando, NULL, 0, NULL);
        if (hThread == NULL)
        {
            return FALSE;
        }
        break;
    case DLL_PROCESS_DETACH:
        if (hThread != NULL)
        {
            TerminateThread(hThread, 0);
            CloseHandle(hThread);
            hThread = NULL;
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
