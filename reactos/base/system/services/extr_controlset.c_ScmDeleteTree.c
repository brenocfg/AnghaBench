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
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteKeyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 

DWORD
ScmDeleteTree(
    HKEY hKey,
    PCWSTR pszSubKey)
{
    DWORD dwMaxSubkeyLength, dwMaxValueLength;
    DWORD dwMaxLength, dwSize;
    PWSTR pszName = NULL;
    HKEY hSubKey = NULL;
    DWORD dwError;

    if (pszSubKey != NULL)
    {
        dwError = RegOpenKeyExW(hKey, pszSubKey, 0, KEY_READ, &hSubKey);
        if (dwError != ERROR_SUCCESS)
            return dwError;
    }
    else
    {
         hSubKey = hKey;
    }

    /* Get highest length for keys, values */
    dwError = RegQueryInfoKeyW(hSubKey,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               &dwMaxSubkeyLength,
                               NULL,
                               NULL,
                               &dwMaxValueLength,
                               NULL,
                               NULL,
                               NULL);
    if (dwError != ERROR_SUCCESS)
        goto done;

    dwMaxSubkeyLength++;
    dwMaxValueLength++;
    dwMaxLength = max(dwMaxSubkeyLength, dwMaxValueLength);

    /* Allocate a buffer for key and value names */
    pszName = HeapAlloc(GetProcessHeap(),
                         0,
                         dwMaxLength * sizeof(WCHAR));
    if (pszName == NULL)
    {
        dwError = ERROR_NOT_ENOUGH_MEMORY;
        goto done;
    }

    /* Recursively delete all the subkeys */
    while (TRUE)
    {
        dwSize = dwMaxLength;
        if (RegEnumKeyExW(hSubKey,
                          0,
                          pszName,
                          &dwSize,
                          NULL,
                          NULL,
                          NULL,
                          NULL))
            break;

        dwError = ScmDeleteTree(hSubKey, pszName);
        if (dwError != ERROR_SUCCESS)
            goto done;
    }

    if (pszSubKey != NULL)
    {
        dwError = RegDeleteKeyW(hKey, pszSubKey);
    }
    else
    {
        while (TRUE)
        {
            dwSize = dwMaxLength;
            if (RegEnumValueW(hKey,
                              0,
                              pszName,
                              &dwSize,
                              NULL,
                              NULL,
                              NULL,
                              NULL))
                break;

            dwError = RegDeleteValueW(hKey, pszName);
            if (dwError != ERROR_SUCCESS)
                goto done;
        }
    }

done:
    if (pszName != NULL)
        HeapFree(GetProcessHeap(), 0, pszName);

    if (pszSubKey != NULL)
        RegCloseKey(hSubKey);

    return dwError;
}