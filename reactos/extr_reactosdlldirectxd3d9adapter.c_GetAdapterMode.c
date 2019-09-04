#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Format; int /*<<< orphan*/  RefreshRate; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_6__ {int dmSize; int dmBitsPerPel; int /*<<< orphan*/  dmDisplayFrequency; int /*<<< orphan*/  dmPelsHeight; int /*<<< orphan*/  dmPelsWidth; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_1__ DEVMODEA ;
typedef  TYPE_2__ D3DDISPLAYMODE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_P8 ; 
 int /*<<< orphan*/  D3DFMT_R8G8B8 ; 
 int /*<<< orphan*/  D3DFMT_UNKNOWN ; 
 int /*<<< orphan*/  D3DFMT_X8R8G8B8 ; 
 int /*<<< orphan*/  ENUM_CURRENT_SETTINGS ; 
 scalar_t__ EnumDisplaySettingsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Get16BitD3DFormat (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOL GetAdapterMode(LPCSTR lpszDeviceName, D3DDISPLAYMODE* pMode)
{
    DEVMODEA DevMode;
    
    memset(&DevMode, 0, sizeof(DEVMODEA));
    DevMode.dmSize = sizeof(DEVMODEA);
    if (FALSE == EnumDisplaySettingsA(lpszDeviceName, ENUM_CURRENT_SETTINGS, &DevMode))
        return FALSE;

    pMode->Width = DevMode.dmPelsWidth;
    pMode->Height = DevMode.dmPelsHeight;
    pMode->RefreshRate = DevMode.dmDisplayFrequency;
    
    switch (DevMode.dmBitsPerPel)
    {
    case 8:
        pMode->Format = D3DFMT_P8;
        break;

    case 16:
        pMode->Format = Get16BitD3DFormat(lpszDeviceName);
        break;

    case 24:
        pMode->Format = D3DFMT_R8G8B8;
        break;

    case 32:
        pMode->Format = D3DFMT_X8R8G8B8;
        break;

    default:
        pMode->Format = D3DFMT_UNKNOWN;
        break;
    }

    return TRUE;
}