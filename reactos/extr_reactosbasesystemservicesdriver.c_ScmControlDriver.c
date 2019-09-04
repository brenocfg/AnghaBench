#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dwCurrentState; int /*<<< orphan*/  dwControlsAccepted; } ;
struct TYPE_7__ {TYPE_1__ Status; } ;
typedef  TYPE_2__* PSERVICE ;
typedef  int /*<<< orphan*/  LPSERVICE_STATUS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int ERROR_INVALID_SERVICE_CONTROL ; 
 int ERROR_SUCCESS ; 
#define  SERVICE_CONTROL_INTERROGATE 129 
#define  SERVICE_CONTROL_STOP 128 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 int /*<<< orphan*/  SERVICE_STOP_PENDING ; 
 int ScmGetDriverStatus (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ScmUnloadDriver (TYPE_2__*) ; 

DWORD
ScmControlDriver(PSERVICE lpService,
                 DWORD dwControl,
                 LPSERVICE_STATUS lpServiceStatus)
{
    DWORD dwError;

    DPRINT("ScmControlDriver() called\n");

    switch (dwControl)
    {
        case SERVICE_CONTROL_STOP:
            /* Check the drivers status */
            dwError = ScmGetDriverStatus(lpService,
                                         lpServiceStatus);
            if (dwError != ERROR_SUCCESS)
                goto done;

            /* Fail, if it is not running */
            if (lpService->Status.dwCurrentState != SERVICE_RUNNING)
            {
                dwError = ERROR_INVALID_SERVICE_CONTROL;
                goto done;
            }

            /* Unload the driver */
            dwError = ScmUnloadDriver(lpService);
            if (dwError == ERROR_INVALID_SERVICE_CONTROL)
            {
                /* The driver cannot be stopped, mark it non-stoppable */
                lpService->Status.dwControlsAccepted = 0;
                goto done;
            }

            /* Make the driver 'stop pending' */
            lpService->Status.dwCurrentState = SERVICE_STOP_PENDING;

            /* Check the drivers status again */
            dwError = ScmGetDriverStatus(lpService,
                                         lpServiceStatus);
            break;

        case SERVICE_CONTROL_INTERROGATE:
            dwError = ScmGetDriverStatus(lpService,
                                         lpServiceStatus);
            break;

        default:
            dwError = ERROR_INVALID_SERVICE_CONTROL;
    }

done:
    DPRINT("ScmControlDriver() done (Erorr: %lu)\n", dwError);

    return dwError;
}