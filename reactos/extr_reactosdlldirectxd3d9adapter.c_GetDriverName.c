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
struct TYPE_6__ {char* Driver; } ;
struct TYPE_5__ {scalar_t__ DeviceKey; } ;
typedef  TYPE_1__* LPDISPLAY_DEVICEA ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  size_t DWORD ;
typedef  TYPE_2__ D3DADAPTER_IDENTIFIER9 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 size_t MAX_DEVICE_IDENTIFIER_STRING ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  SafeAppendString (char*,size_t,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static BOOL GetDriverName(LPDISPLAY_DEVICEA pDisplayDevice, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    HKEY hKey;
    BOOL bResult = FALSE;

    if (ERROR_SUCCESS == RegOpenKeyExA(HKEY_LOCAL_MACHINE, pDisplayDevice->DeviceKey + strlen("\\Registry\\Machine\\"), 0, KEY_QUERY_VALUE, &hKey))
    {
        DWORD DriverNameLength = MAX_DEVICE_IDENTIFIER_STRING - (DWORD)strlen(".dll");
        DWORD Type = 0;

        if (ERROR_SUCCESS == RegQueryValueExA(hKey, "InstalledDisplayDrivers", 0, &Type, (LPBYTE)pIdentifier->Driver, &DriverNameLength))
        {
            pIdentifier->Driver[DriverNameLength] = '\0';
            SafeAppendString(pIdentifier->Driver, MAX_DEVICE_IDENTIFIER_STRING, ".dll");
            bResult = TRUE;
        }

        RegCloseKey(hKey);
    }

    return bResult;
}