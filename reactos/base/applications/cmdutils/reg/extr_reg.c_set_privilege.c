#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int PrivilegeCount; TYPE_1__* Privileges; } ;
struct TYPE_4__ {int /*<<< orphan*/  Luid; int /*<<< orphan*/  Attributes; } ;
typedef  TYPE_2__ TOKEN_PRIVILEGES ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AdjustTokenPrivileges (scalar_t__,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_NOT_ALL_ASSIGNED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ LookupPrivilegeValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SE_PRIVILEGE_ENABLED ; 
 int /*<<< orphan*/  TOKEN_ADJUST_PRIVILEGES ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  output_error (scalar_t__) ; 

__attribute__((used)) static BOOL set_privilege(LPCWSTR privilegeName, BOOL enabled)
{
    HANDLE hToken = INVALID_HANDLE_VALUE;
    TOKEN_PRIVILEGES tp;
    DWORD error = ERROR_SUCCESS;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = (enabled ? SE_PRIVILEGE_ENABLED : 0);

        if (LookupPrivilegeValueW(NULL, privilegeName, &tp.Privileges[0].Luid))
        {
            if (AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL))
            {
                if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
                {
                    error = ERROR_NOT_ALL_ASSIGNED;
                    goto fail;
                }
            }
            else
            {
                error = GetLastError();
                goto fail;
            }
        }
        else
        {
            error = GetLastError();
            goto fail;
        }
    }
    else
    {
        error = GetLastError();
        goto fail;
    }

    CloseHandle(hToken);
    return TRUE;

fail:
    // Don't allow a success error to be printed, as that would confuse the user.
    // "Access denied" seems like a reasonable default.
    if (error == ERROR_SUCCESS) error = ERROR_ACCESS_DENIED;
    if (hToken != INVALID_HANDLE_VALUE) CloseHandle(hToken);

    output_error(error);
    return FALSE;
}