#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  Description; } ;
struct TYPE_12__ {int cb; int /*<<< orphan*/  DeviceID; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  DeviceString; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DISPLAY_DEVICEA ;
typedef  TYPE_2__ D3DADAPTER_IDENTIFIER9 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CCHDEVICENAME ; 
 scalar_t__ EnumDisplayDevicesA (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GenerateDeviceIdentifier (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDeviceId (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ GetDriverName (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  GetDriverVersion (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MAX_DEVICE_IDENTIFIER_STRING ; 
 scalar_t__ TRUE ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpynA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOL GetAdapterInfo(LPCSTR lpszDeviceName, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    DISPLAY_DEVICEA DisplayDevice;
    DWORD AdapterIndex;
    BOOL FoundDisplayDevice;

    memset(&DisplayDevice, 0, sizeof(DISPLAY_DEVICEA));
    DisplayDevice.cb = sizeof(DISPLAY_DEVICEA);   

    AdapterIndex = 0;
    FoundDisplayDevice = FALSE;
    while (EnumDisplayDevicesA(NULL, AdapterIndex, &DisplayDevice, 0) != FALSE)
    {
        if (_stricmp(lpszDeviceName, DisplayDevice.DeviceName) == 0)
        {
            FoundDisplayDevice = TRUE;
            break;
        }

        ++AdapterIndex;
    }

    /* No matching display device found? */
    if (FALSE == FoundDisplayDevice)
        return FALSE;

    lstrcpynA(pIdentifier->Description, DisplayDevice.DeviceString, MAX_DEVICE_IDENTIFIER_STRING);
    lstrcpynA(pIdentifier->DeviceName, DisplayDevice.DeviceName, CCHDEVICENAME);

    if (GetDriverName(&DisplayDevice, pIdentifier) != FALSE)
        GetDriverVersion(&DisplayDevice, pIdentifier);

    GetDeviceId(DisplayDevice.DeviceID, pIdentifier);

    GenerateDeviceIdentifier(pIdentifier);

    return TRUE;
}