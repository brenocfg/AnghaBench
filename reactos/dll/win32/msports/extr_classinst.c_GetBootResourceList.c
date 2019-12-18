#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  PSP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/ * PCM_RESOURCE_LIST ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  HDEVINFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (char*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupDiGetDeviceInstanceIdW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

BOOL
GetBootResourceList(HDEVINFO DeviceInfoSet,
                    PSP_DEVINFO_DATA DeviceInfoData,
                    PCM_RESOURCE_LIST *ppResourceList)
{
    WCHAR DeviceInstanceIdBuffer[128];
    HKEY hEnumKey = NULL;
    HKEY hDeviceKey = NULL;
    HKEY hConfigKey = NULL;
    LPBYTE lpBuffer = NULL;
    DWORD dwDataSize;
    LONG lError;
    BOOL ret = FALSE;

    FIXME("GetBootResourceList()\n");

    *ppResourceList = NULL;

    if (!SetupDiGetDeviceInstanceIdW(DeviceInfoSet,
                                     DeviceInfoData,
                                     DeviceInstanceIdBuffer,
                                     ARRAYSIZE(DeviceInstanceIdBuffer),
                                     &dwDataSize))
    {
        ERR("SetupDiGetDeviceInstanceIdW() failed\n");
        return FALSE;
    }

    lError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                           L"SYSTEM\\CurrentControlSet\\Enum",
                           0,
                           KEY_QUERY_VALUE,
                           &hEnumKey);
    if (lError != ERROR_SUCCESS)
    {
        ERR("RegOpenKeyExW() failed (Error %lu)\n", lError);
        goto done;
    }

    lError = RegOpenKeyExW(hEnumKey,
                           DeviceInstanceIdBuffer,
                           0,
                           KEY_QUERY_VALUE,
                           &hDeviceKey);
    if (lError != ERROR_SUCCESS)
    {
        ERR("RegOpenKeyExW() failed (Error %lu)\n", lError);
        goto done;
    }

    lError = RegOpenKeyExW(hDeviceKey,
                           L"LogConf",
                           0,
                           KEY_QUERY_VALUE,
                           &hConfigKey);
    if (lError != ERROR_SUCCESS)
    {
        ERR("RegOpenKeyExW() failed (Error %lu)\n", lError);
        goto done;
    }

    /* Get the configuration data size */
    lError = RegQueryValueExW(hConfigKey,
                              L"BootConfig",
                              NULL,
                              NULL,
                              NULL,
                              &dwDataSize);
    if (lError != ERROR_SUCCESS)
    {
        ERR("RegQueryValueExW() failed (Error %lu)\n", lError);
        goto done;
    }

    /* Allocate the buffer */
    lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwDataSize);
    if (lpBuffer == NULL)
    {
        ERR("Failed to allocate the resource list buffer\n");
        goto done;
    }

    /* Retrieve the configuration data */
    lError = RegQueryValueExW(hConfigKey,
                              L"BootConfig",
                              NULL,
                              NULL,
                             (LPBYTE)lpBuffer,
                              &dwDataSize);
    if (lError == ERROR_SUCCESS)
    {
        ERR("RegQueryValueExW() failed (Error %lu)\n", lError);
        ret = TRUE;
    }

done:
    if (ret == FALSE && lpBuffer != NULL)
        HeapFree(GetProcessHeap(), 0, lpBuffer);

    if (hConfigKey)
        RegCloseKey(hConfigKey);

    if (hDeviceKey)
        RegCloseKey(hDeviceKey);

    if (hEnumKey)
        RegCloseKey(hEnumKey);

    if (ret != FALSE)
        *ppResourceList = (PCM_RESOURCE_LIST)lpBuffer;

    return ret;
}