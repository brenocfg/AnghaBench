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
typedef  int /*<<< orphan*/  previouspriv ;
struct TYPE_6__ {int PrivilegeCount; TYPE_1__* Privileges; } ;
struct TYPE_5__ {int /*<<< orphan*/  Luid; int /*<<< orphan*/  Attributes; } ;
typedef  TYPE_2__ TOKEN_PRIVILEGES ;
typedef  int /*<<< orphan*/  LPSYSTEMTIME ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ AdjustTokenPrivileges (int /*<<< orphan*/ ,int,TYPE_2__*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ LookupPrivilegeValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SE_PRIVILEGE_ENABLED ; 
 int /*<<< orphan*/  SE_SYSTEMTIME_NAME ; 
 scalar_t__ SetLocalTime (int /*<<< orphan*/ ) ; 
 int TOKEN_ADJUST_PRIVILEGES ; 
 int TOKEN_QUERY ; 

BOOL
SystemSetLocalTime(LPSYSTEMTIME lpSystemTime)
{
    HANDLE hToken;
    DWORD PrevSize;
    TOKEN_PRIVILEGES priv, previouspriv;
    BOOL Ret = FALSE;

    /*
     * Enable the SeSystemtimePrivilege privilege
     */

    if (OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                         &hToken))
    {
        priv.PrivilegeCount = 1;
        priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if (LookupPrivilegeValueW(NULL,
                                  SE_SYSTEMTIME_NAME,
                                  &priv.Privileges[0].Luid))
        {
            if (AdjustTokenPrivileges(hToken,
                                      FALSE,
                                      &priv,
                                      sizeof(previouspriv),
                                      &previouspriv,
                                      &PrevSize) &&
                GetLastError() == ERROR_SUCCESS)
            {
                /*
                 * We successfully enabled it, we're permitted to change the time.
                 * Call SetLocalTime twice to ensure correct results.
                 */
                Ret = SetLocalTime(lpSystemTime) &&
                      SetLocalTime(lpSystemTime);

                /*
                 * For the sake of security, restore the previous status again
                 */
                if (previouspriv.PrivilegeCount > 0)
                {
                    AdjustTokenPrivileges(hToken,
                                          FALSE,
                                          &previouspriv,
                                          0,
                                          NULL,
                                          0);
                }
            }
        }
        CloseHandle(hToken);
    }

    return Ret;
}