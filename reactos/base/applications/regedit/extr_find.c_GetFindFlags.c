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
typedef  int /*<<< orphan*/  dwValue ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ RSF_LOOKATDATA ; 
 scalar_t__ RSF_LOOKATKEYS ; 
 scalar_t__ RSF_LOOKATVALUES ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  g_szGeneralRegKey ; 
 int /*<<< orphan*/  s_szFindFlags ; 
 int /*<<< orphan*/  s_szFindFlagsR ; 

__attribute__((used)) static DWORD GetFindFlags(void)
{
    HKEY hKey;
    DWORD dwType, dwValue, cbData;
    DWORD dwFlags = RSF_LOOKATKEYS | RSF_LOOKATVALUES | RSF_LOOKATDATA;

    if (RegOpenKeyW(HKEY_CURRENT_USER, g_szGeneralRegKey, &hKey) == ERROR_SUCCESS)
    {
        /* Retrieve flags from registry key */
        cbData = sizeof(dwValue);
        if (RegQueryValueExW(hKey, s_szFindFlags, NULL, &dwType, (LPBYTE) &dwValue, &cbData) == ERROR_SUCCESS)
        {
            if (dwType == REG_DWORD)
                dwFlags = (dwFlags & ~0x0000FFFF) | ((dwValue & 0x0000FFFF) << 0);
        }

        /* Retrieve ReactOS Regedit specific flags from registry key */
        cbData = sizeof(dwValue);
        if (RegQueryValueExW(hKey, s_szFindFlagsR, NULL, &dwType, (LPBYTE) &dwValue, &cbData) == ERROR_SUCCESS)
        {
            if (dwType == REG_DWORD)
                dwFlags = (dwFlags & ~0xFFFF0000) | ((dwValue & 0x0000FFFF) << 16);
        }

        RegCloseKey(hKey);
    }
    return dwFlags;
}