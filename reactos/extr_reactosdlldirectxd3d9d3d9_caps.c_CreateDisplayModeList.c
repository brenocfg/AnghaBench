#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Format; int /*<<< orphan*/  RefreshRate; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_5__ {int dmBitsPerPel; int /*<<< orphan*/  dmDisplayFrequency; int /*<<< orphan*/  dmPelsHeight; int /*<<< orphan*/  dmPelsWidth; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DEVMODEA ;
typedef  int /*<<< orphan*/  D3DFORMAT ;
typedef  TYPE_2__ D3DDISPLAYMODE ;
typedef  int /*<<< orphan*/  D3D9_Unknown6BC ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_X8R8G8B8 ; 
 scalar_t__ EnumDisplaySettingsA (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 scalar_t__ TRUE ; 

void CreateDisplayModeList(LPCSTR lpszDeviceName, D3DDISPLAYMODE* pDisplayModes, DWORD* pNumDisplayModes, D3DFORMAT Default16BitFormat, D3D9_Unknown6BC* pUnknown6BC)
{
    DEVMODEA DevMode;
    DWORD ModeIndex = 0;
    DWORD ValidModes = 0;

    while (TRUE == EnumDisplaySettingsA(lpszDeviceName, ModeIndex, &DevMode))
    {
        D3DFORMAT DefaultFormat;

        if (DevMode.dmBitsPerPel != 15 &&
            DevMode.dmBitsPerPel != 16 &&
            DevMode.dmBitsPerPel != 32)
        {
            ++ModeIndex;
            continue;
        }

        ++ValidModes;

        if (DevMode.dmBitsPerPel == 15 || DevMode.dmBitsPerPel == 16)
        {
            if (NULL == pUnknown6BC)
            {
                ++ModeIndex;
                continue;
            }

            DefaultFormat = Default16BitFormat;
        }
        else
        {
            DefaultFormat = D3DFMT_X8R8G8B8;
        }

        if (NULL != pDisplayModes)
        {
            if (ValidModes == *pNumDisplayModes)
                break;

            pDisplayModes->Width = DevMode.dmPelsWidth;
            pDisplayModes->Height = DevMode.dmPelsHeight;
            pDisplayModes->RefreshRate = DevMode.dmDisplayFrequency;
            pDisplayModes->Format = DefaultFormat;
            ++pDisplayModes;
        }

        ++ModeIndex;
    }

    *pNumDisplayModes = ValidModes;
}