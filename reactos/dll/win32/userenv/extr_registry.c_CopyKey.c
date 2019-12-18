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
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCopyTreeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
CopyKey(HKEY hDstKey,
        HKEY hSrcKey)
{
    LONG Error;

#if (_WIN32_WINNT >= 0x0600)
    Error = RegCopyTreeW(hSrcKey,
                         NULL,
                         hDstKey);
    if (Error != ERROR_SUCCESS)
    {
        SetLastError((DWORD)Error);
        return FALSE;
    }

    return TRUE;

#else
    FILETIME LastWrite;
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

    DPRINT ("CopyKey() called \n");

    Error = RegQueryInfoKey(hSrcKey,
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
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegQueryInfoKey() failed (Error %lu)\n", Error);
        SetLastError((DWORD)Error);
        return FALSE;
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
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FALSE;
        }

        for (i = 0; i < dwSubKeys; i++)
        {
            dwSubKeyNameLength = dwMaxSubKeyNameLength;
            Error = RegEnumKeyExW(hSrcKey,
                                  i,
                                  lpNameBuffer,
                                  &dwSubKeyNameLength,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &LastWrite);
            if (Error != ERROR_SUCCESS)
            {
                DPRINT1("Subkey enumeration failed (Error %lu)\n", Error);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                SetLastError((DWORD)Error);
                return FALSE;
            }

            Error = RegCreateKeyExW(hDstKey,
                                    lpNameBuffer,
                                    0,
                                    NULL,
                                    REG_OPTION_NON_VOLATILE,
                                    KEY_WRITE,
                                    NULL,
                                    &hDstSubKey,
                                    &dwDisposition);
            if (Error != ERROR_SUCCESS)
            {
                DPRINT1("Subkey creation failed (Error %lu)\n", Error);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                SetLastError((DWORD)Error);
                return FALSE;
            }

            Error = RegOpenKeyExW(hSrcKey,
                                  lpNameBuffer,
                                  0,
                                  KEY_READ,
                                  &hSrcSubKey);
            if (Error != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", Error);
                RegCloseKey(hDstSubKey);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                SetLastError((DWORD)Error);
                return FALSE;
            }

            if (!CopyKey(hDstSubKey,
                         hSrcSubKey))
            {
                DPRINT1("Error: %lu\n", GetLastError());
                RegCloseKey (hSrcSubKey);
                RegCloseKey (hDstSubKey);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                return FALSE;
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
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FALSE;
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
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FALSE;
        }

        for (i = 0; i < dwValues; i++)
        {
            dwValueNameLength = dwMaxValueNameLength;
            dwValueLength = dwMaxValueLength;
            Error = RegEnumValueW(hSrcKey,
                                  i,
                                  lpNameBuffer,
                                  &dwValueNameLength,
                                  NULL,
                                  &dwType,
                                  lpDataBuffer,
                                  &dwValueLength);
            if (Error != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", Error);
                HeapFree(GetProcessHeap(),
                         0,
                         lpDataBuffer);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                SetLastError((DWORD)Error);
                return FALSE;
            }

            Error = RegSetValueExW(hDstKey,
                                   lpNameBuffer,
                                   0,
                                   dwType,
                                   lpDataBuffer,
                                   dwValueLength);
            if (Error != ERROR_SUCCESS)
            {
                DPRINT1("Error: %lu\n", Error);
                HeapFree(GetProcessHeap(),
                         0,
                         lpDataBuffer);
                HeapFree(GetProcessHeap(),
                         0,
                         lpNameBuffer);
                SetLastError((DWORD)Error);
                return FALSE;
            }
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpDataBuffer);

        HeapFree(GetProcessHeap(),
                 0,
                 lpNameBuffer);
    }

    DPRINT("CopyKey() done \n");

    return TRUE;
#endif
}