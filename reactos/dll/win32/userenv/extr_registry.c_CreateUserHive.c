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
typedef  char* LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegFlushKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateUsersShellFolderSettings (char*,int /*<<< orphan*/ *) ; 

BOOL
CreateUserHive(LPCWSTR lpKeyName,
               LPCWSTR lpProfilePath)
{
    HKEY hDefaultKey = NULL;
    HKEY hUserKey = NULL;
    LONG Error;
    BOOL Ret = FALSE;

    DPRINT("CreateUserHive(%S) called\n", lpKeyName);

    Error = RegOpenKeyExW(HKEY_USERS,
                          L".Default",
                          0,
                          KEY_READ,
                          &hDefaultKey);
    if (Error != ERROR_SUCCESS)
    {
        SetLastError((DWORD)Error);
        goto Cleanup;
    }

    Error = RegOpenKeyExW(HKEY_USERS,
                          lpKeyName,
                          0,
                          KEY_ALL_ACCESS,
                          &hUserKey);
    if (Error != ERROR_SUCCESS)
    {
        SetLastError((DWORD)Error);
        goto Cleanup;
    }

    if (!CopyKey(hUserKey, hDefaultKey))
    {
        goto Cleanup;
    }

    if (!UpdateUsersShellFolderSettings(lpProfilePath,
                                        hUserKey))
    {
        goto Cleanup;
    }

    RegFlushKey(hUserKey);
    Ret = TRUE;

Cleanup:
    if (hUserKey != NULL)
        RegCloseKey (hUserKey);

    if (hDefaultKey != NULL)
        RegCloseKey (hDefaultKey);

    return Ret;
}