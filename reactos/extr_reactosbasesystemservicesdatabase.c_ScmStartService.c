#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lpServiceName; } ;
typedef  int /*<<< orphan*/ * SC_RPC_LOCK ;
typedef  TYPE_1__* PSERVICE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ControlServiceCriticalSection ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ ScmAcquireServiceStartLock (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ScmInitialize ; 
 scalar_t__ ScmLoadService (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScmReleaseServiceStartLock (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 

DWORD
ScmStartService(PSERVICE Service,
                DWORD argc,
                LPWSTR* argv)
{
    DWORD dwError = ERROR_SUCCESS;
    SC_RPC_LOCK Lock = NULL;

    DPRINT("ScmStartService() called\n");
    DPRINT("Start Service %p (%S)\n", Service, Service->lpServiceName);

    /* Acquire the service control critical section, to synchronize starts */
    EnterCriticalSection(&ControlServiceCriticalSection);

    /*
     * Acquire the user service start lock while the service is starting, if
     * needed (i.e. if we are not starting it during the initialization phase).
     * If we don't success, bail out.
     */
    if (!ScmInitialize)
    {
        dwError = ScmAcquireServiceStartLock(TRUE, &Lock);
        if (dwError != ERROR_SUCCESS) goto done;
    }

    /* Really start the service */
    dwError = ScmLoadService(Service, argc, argv);

    /* Release the service start lock, if needed, and the critical section */
    if (Lock) ScmReleaseServiceStartLock(&Lock);

done:
    LeaveCriticalSection(&ControlServiceCriticalSection);

    DPRINT("ScmStartService() done (Error %lu)\n", dwError);

    return dwError;
}