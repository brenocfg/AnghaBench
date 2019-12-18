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
typedef  scalar_t__ pid_t ;
struct TYPE_6__ {scalar_t__ pid; scalar_t__ workerStatus; uintptr_t hThread; } ;
struct TYPE_5__ {int numWorkers; int /*<<< orphan*/ ** te; TYPE_2__* parallelSlot; } ;
typedef  TYPE_1__ ParallelState ;
typedef  TYPE_2__ ParallelSlot ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  HasEveryWorkerTerminated (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WRKR_TERMINATED ; 
 scalar_t__ WaitForMultipleObjects (int,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* pg_malloc (int) ; 
 scalar_t__ wait (int*) ; 

__attribute__((used)) static void
WaitForTerminatingWorkers(ParallelState *pstate)
{
	while (!HasEveryWorkerTerminated(pstate))
	{
		ParallelSlot *slot = NULL;
		int			j;

#ifndef WIN32
		/* On non-Windows, use wait() to wait for next worker to end */
		int			status;
		pid_t		pid = wait(&status);

		/* Find dead worker's slot, and clear the PID field */
		for (j = 0; j < pstate->numWorkers; j++)
		{
			slot = &(pstate->parallelSlot[j]);
			if (slot->pid == pid)
			{
				slot->pid = 0;
				break;
			}
		}
#else							/* WIN32 */
		/* On Windows, we must use WaitForMultipleObjects() */
		HANDLE	   *lpHandles = pg_malloc(sizeof(HANDLE) * pstate->numWorkers);
		int			nrun = 0;
		DWORD		ret;
		uintptr_t	hThread;

		for (j = 0; j < pstate->numWorkers; j++)
		{
			if (pstate->parallelSlot[j].workerStatus != WRKR_TERMINATED)
			{
				lpHandles[nrun] = (HANDLE) pstate->parallelSlot[j].hThread;
				nrun++;
			}
		}
		ret = WaitForMultipleObjects(nrun, lpHandles, false, INFINITE);
		Assert(ret != WAIT_FAILED);
		hThread = (uintptr_t) lpHandles[ret - WAIT_OBJECT_0];
		free(lpHandles);

		/* Find dead worker's slot, and clear the hThread field */
		for (j = 0; j < pstate->numWorkers; j++)
		{
			slot = &(pstate->parallelSlot[j]);
			if (slot->hThread == hThread)
			{
				/* For cleanliness, close handles for dead threads */
				CloseHandle((HANDLE) slot->hThread);
				slot->hThread = (uintptr_t) INVALID_HANDLE_VALUE;
				break;
			}
		}
#endif							/* WIN32 */

		/* On all platforms, update workerStatus and te[] as well */
		Assert(j < pstate->numWorkers);
		slot->workerStatus = WRKR_TERMINATED;
		pstate->te[j] = NULL;
	}
}