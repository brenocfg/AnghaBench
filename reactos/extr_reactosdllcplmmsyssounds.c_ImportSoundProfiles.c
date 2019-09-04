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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ ImportAppProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKey (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 

BOOL
ImportSoundProfiles(PGLOBAL_DATA pGlobalData, HWND hwndDlg, HKEY hKey)
{
    DWORD dwCurKey;
    DWORD dwResult;
    DWORD dwNumApps;
    TCHAR szName[MAX_PATH];
    HKEY hSubKey;

    if (RegOpenKeyEx(hKey,
                     _T("Apps"),
                     0,
                     KEY_READ,
                     &hSubKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    dwNumApps = 0;
    dwCurKey = 0;
    do
    {
        dwResult = RegEnumKey(hSubKey,
                              dwCurKey,
                              szName,
                              _countof(szName));

        if (dwResult == ERROR_SUCCESS)
        {
            if (ImportAppProfile(pGlobalData, hwndDlg, hSubKey, szName))
            {
                dwNumApps++;
            }
        }
        dwCurKey++;
    } while (dwResult == ERROR_SUCCESS);

    RegCloseKey(hSubKey);

    return (dwNumApps != 0);
}