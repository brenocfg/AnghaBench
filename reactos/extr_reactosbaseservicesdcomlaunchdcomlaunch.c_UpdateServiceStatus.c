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
struct TYPE_3__ {int dwWaitHint; scalar_t__ dwCheckPoint; scalar_t__ dwServiceSpecificExitCode; scalar_t__ dwWin32ExitCode; scalar_t__ dwControlsAccepted; scalar_t__ dwCurrentState; int /*<<< orphan*/  dwServiceType; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ SERVICE_CONTINUE_PENDING ; 
 scalar_t__ SERVICE_PAUSE_PENDING ; 
 scalar_t__ SERVICE_START_PENDING ; 
 scalar_t__ SERVICE_STOP_PENDING ; 
 int /*<<< orphan*/  SERVICE_WIN32_OWN_PROCESS ; 
 TYPE_1__ ServiceStatus ; 
 int /*<<< orphan*/  ServiceStatusHandle ; 
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static VOID
UpdateServiceStatus(DWORD dwState)
{
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = dwState;
    ServiceStatus.dwControlsAccepted = 0;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;

    if (dwState == SERVICE_START_PENDING ||
        dwState == SERVICE_STOP_PENDING ||
        dwState == SERVICE_PAUSE_PENDING ||
        dwState == SERVICE_CONTINUE_PENDING)
        ServiceStatus.dwWaitHint = 10000;
    else
        ServiceStatus.dwWaitHint = 0;

    SetServiceStatus(ServiceStatusHandle,
                     &ServiceStatus);
}