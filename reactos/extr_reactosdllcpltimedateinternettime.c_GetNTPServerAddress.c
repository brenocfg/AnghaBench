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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayWin32Error (scalar_t__) ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegQueryValueExW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
GetNTPServerAddress(LPWSTR *lpAddress)
{
    HKEY hKey;
    WCHAR szSel[4];
    DWORD dwSize;
    LONG lRet;

    lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                         L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DateTime\\Servers",
                         0,
                         KEY_QUERY_VALUE,
                         &hKey);
    if (lRet != ERROR_SUCCESS)
        goto fail;

    /* Get data from default value */
    dwSize = 4 * sizeof(WCHAR);
    lRet = RegQueryValueExW(hKey,
                            NULL,
                            NULL,
                            NULL,
                            (LPBYTE)szSel,
                            &dwSize);
    if (lRet != ERROR_SUCCESS)
        goto fail;

    dwSize = 0;
    lRet = RegQueryValueExW(hKey,
                            szSel,
                            NULL,
                            NULL,
                            NULL,
                            &dwSize);
    if (lRet != ERROR_SUCCESS)
        goto fail;

    (*lpAddress) = (LPWSTR)HeapAlloc(GetProcessHeap(),
                                     0,
                                     dwSize);
    if ((*lpAddress) == NULL)
    {
        lRet = ERROR_NOT_ENOUGH_MEMORY;
        goto fail;
    }

    lRet = RegQueryValueExW(hKey,
                            szSel,
                            NULL,
                            NULL,
                            (LPBYTE)*lpAddress,
                            &dwSize);
    if (lRet != ERROR_SUCCESS)
        goto fail;

    RegCloseKey(hKey);

    return TRUE;

fail:
    DisplayWin32Error(lRet);
    if (hKey)
        RegCloseKey(hKey);
    HeapFree(GetProcessHeap(), 0, *lpAddress);
    return FALSE;
}