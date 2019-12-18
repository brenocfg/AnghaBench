#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwControlsAccepted; scalar_t__ dwWaitHint; scalar_t__ dwCheckPoint; scalar_t__ dwServiceSpecificExitCode; scalar_t__ dwWin32ExitCode; scalar_t__ dwCurrentState; int /*<<< orphan*/  dwServiceType; } ;
typedef  TYPE_1__ SERVICE_STATUS ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SERVICE_SPECIFIC_ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KillService () ; 
 int SERVICE_ACCEPT_PAUSE_CONTINUE ; 
 int SERVICE_ACCEPT_SHUTDOWN ; 
 int SERVICE_ACCEPT_STOP ; 
 scalar_t__ SERVICE_START_PENDING ; 
 scalar_t__ SERVICE_STOPPED ; 
 scalar_t__ SERVICE_STOP_PENDING ; 
 int /*<<< orphan*/  SERVICE_WIN32_OWN_PROCESS ; 
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hstatus ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BOOL UpdateSCMStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode,
                            DWORD dwServiceSpecificExitCode)
{
    SERVICE_STATUS status;

    status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    status.dwCurrentState = dwCurrentState;

    if (dwCurrentState == SERVICE_START_PENDING
            || dwCurrentState == SERVICE_STOP_PENDING
            || dwCurrentState == SERVICE_STOPPED)
        status.dwControlsAccepted = 0;
    else
    {
        status.dwControlsAccepted = SERVICE_ACCEPT_STOP |
                                    SERVICE_ACCEPT_PAUSE_CONTINUE |
                                    SERVICE_ACCEPT_SHUTDOWN;
    }

    if (dwServiceSpecificExitCode == 0)
    {
        status.dwWin32ExitCode = dwWin32ExitCode;
    }
    else
    {
        status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
    }

    status.dwServiceSpecificExitCode = dwServiceSpecificExitCode;
    status.dwCheckPoint = 0;
    status.dwWaitHint = 0;

    if (!SetServiceStatus(hstatus, &status))
    {
        fprintf(stderr, "Failed to set service status\n");
        KillService();
        return FALSE;
    }

    return TRUE;
}