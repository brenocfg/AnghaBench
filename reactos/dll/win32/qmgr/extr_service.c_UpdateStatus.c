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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dwControlsAccepted; scalar_t__ dwWaitHint; scalar_t__ dwCheckPoint; scalar_t__ dwServiceSpecificExitCode; scalar_t__ dwWin32ExitCode; scalar_t__ dwCurrentState; int /*<<< orphan*/  dwServiceType; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int SERVICE_ACCEPT_PAUSE_CONTINUE ; 
 int SERVICE_ACCEPT_SHUTDOWN ; 
 int SERVICE_ACCEPT_STOP ; 
 scalar_t__ SERVICE_START_PENDING ; 
 int /*<<< orphan*/  SERVICE_WIN32_OWN_PROCESS ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ status ; 
 int /*<<< orphan*/  status_handle ; 
 int /*<<< orphan*/  stop_event ; 

__attribute__((used)) static VOID
UpdateStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
{
    status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    status.dwCurrentState = dwCurrentState;
    if (dwCurrentState == SERVICE_START_PENDING)
        status.dwControlsAccepted = 0;
    else
        status.dwControlsAccepted
            = (SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE
               | SERVICE_ACCEPT_SHUTDOWN);
    status.dwWin32ExitCode = 0;
    status.dwServiceSpecificExitCode = 0;
    status.dwCheckPoint = 0;
    status.dwWaitHint = dwWaitHint;

    if (!SetServiceStatus(status_handle, &status)) {
        ERR("failed to set service status\n");
        SetEvent(stop_event);
    }
}