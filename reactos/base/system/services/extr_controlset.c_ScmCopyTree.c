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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static
DWORD
ScmCopyTree(
    HKEY hSrcKey,
    HKEY hDstKey)
{
    DWORD dwSubKeys;
    DWORD dwValues;
    DWORD dwType;
    DWORD dwMaxSubKeyNameLength;
    DWORD dwSubKeyNameLength;
    DWORD dwMaxValueNameLength;
    DWORD dwValueNameLength;
    DWORD dwMaxValueLength;
    DWORD dwValueLength;
    DWORD dwDisposition;
    DWORD i;
    LPWSTR lpNameBuffer;
    LPBYTE lpDataBuffer;
    HKEY hDstSubKey;
    HKEY hSrcSubKey;
    DWORD dwError;

    DPRINT("ScmCopyTree()\n");

    dwError = RegQueryInfoKey(hSrcKey,
                              NULL,
                              NULL,
                              NULL,
                              &dwSubKeys,
                              &dwMaxSubKeyNameLength,
                              NULL,
                              &dwValues,
                              &dwMaxValueNameLength,
                              &dwMaxValueLength,
                              NULL,
                              NULL);
    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("RegQueryInfoKey() failed (Error %lu)\n", dwError);
        return dwError;
    }

    dwMaxSubKeyNameLength++;
    dwMaxValueNameLength++;

    DPRINT("dwSubKeys %lu\n", dwSubKeys);
    DPRINT("dwMaxSubKeyNameLength %lu\n", dwMaxSubKeyNameLength);
    DPRINT("dwValues %lu\n", dwValues);
    DPRINT("dwMaxValueNameLength %lu\n", dwMaxValueNameLength);
    DPRINT("dwMaxValueLength %lu\n", dwMaxValueLength);

    /* Copy subkeys */
    if (dwSubKeys != 0)
    {
        lpNameBuffer = HeapAlloc(GetProcessHeap(),
                                 0,
                                 dwMaxSubKeyNameLength * sizeof(WCHAR));
        if (lpNameBuffer == NULL)
        {
            DPRINT1("Buffer allocation failed\n");
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        for (i = 0; i < dwSubKeys; i++)
        {
            dwSubKeyNameLength = dwMaxSubKeyNameLength;
            dwError = RegEnumKeyExW(hSrcKey,
                                    i,
                                    lpNameBuffer,
                                    &dwSubKeyNameLength,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
            if (dwError != ERROR_SUCCESS)
            {
                DPRINT1("Subkey enumeration failed (Error %lu)\n", dwError);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return dwError;
            }

            dwError = RegCreateKeyExW(hDstKey,
                                      lpNameBuffer,
                                      0,
                                      NULL,
                                      REG_OPTION_NON_VOLATILE,
                                      KEY_WRITE,
                                      NULL,
                                      &hDstSubKey,
                                      &dwDisposition);
            if (dwError != ERROR_SUCCESS)
            {
                DPRINT1("Subkey creation failed (Error %lu)\n", dwError);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return dwError;
            }

            dwError = RegOpenKeyExW(hSrcKey,
                                    lpNameBuffer,
                                    0,
                                    KEY_READ,
                                    &hSrcSubKey);
            if (dwError != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", dwError);
                RegCloseKey(hDstSubKey);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return dwError;
            }

            dwError = ScmCopyTree(hSrcSubKey,
                                  hDstSubKey);
            if (dwError != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", dwError);
                RegCloseKey (hSrcSubKey);
                RegCloseKey (hDstSubKey);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return dwError;
            }

            RegCloseKey(hSrcSubKey);
            RegCloseKey(hDstSubKey);
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpNameBuffer);
    }

    /* Copy values */
    if (dwValues != 0)
    {
        lpNameBuffer = HeapAlloc(GetProcessHeap(),
                                 0,
                                 dwMaxValueNameLength * sizeof(WCHAR));
        if (lpNameBuffer == NULL)
        {
            DPRINT1("Buffer allocation failed\n");
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        lpDataBuffer = HeapAlloc(GetProcessHeap(),
                                 0,
                                 dwMaxValueLength);
        if (lpDataBuffer == NULL)
        {
            DPRINT1("Buffer allocation failed\n");
            HeapFree(GetProcessHeap(),
                     0,
                     lpNameBuffer);
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        for (i = 0; i < dwValues; i++)
        {
            dwValueNameLength = dwMaxValueNameLength;
            dwValueLength = dwMaxValueLength;
            dwError = RegEnumValueW(hSrcKey,
                                    i,
                                    lpNameBuffer,
                                    &dwValueNameLength,
                                    NULL,
                                    &dwType,
                                    lpDataBuffer,
                                    &dwValueLength);
            if (dwError != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", dwError);
                HeapFree(GetProcessHeap(),
                         0,
                         lpDataBuffer);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return dwError;
            }

            dwError = RegSetValueExW(hDstKey,
                                     lpNameBuffer,
                                     0,
                                     dwType,
                                     lpDataBuffer,
                                     dwValueLength);
            if (dwError != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", dwError);
                HeapFree(GetProcessHeap(),
                         0,
                         lpDataBuffer);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return dwError;
            }
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpDataBuffer);

        HeapFree(GetProcessHeap(),
                 0,
                 lpNameBuffer);
    }

    DPRINT("ScmCopyTree() done \n");

    return ERROR_SUCCESS;
}