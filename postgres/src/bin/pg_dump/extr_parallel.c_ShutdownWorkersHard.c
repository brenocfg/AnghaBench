#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_8__ {int /*<<< orphan*/ * connCancel; } ;
struct TYPE_7__ {int numWorkers; TYPE_1__* parallelSlot; } ;
struct TYPE_6__ {scalar_t__ pid; TYPE_3__* AH; int /*<<< orphan*/  pipeWrite; } ;
typedef  TYPE_2__ ParallelState ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQcancel (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  WaitForTerminatingWorkers (TYPE_2__*) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_info_lock ; 

__attribute__((used)) static void
ShutdownWorkersHard(ParallelState *pstate)
{
	int			i;

	/*
	 * Close our write end of the sockets so that any workers waiting for
	 * commands know they can exit.
	 */
	for (i = 0; i < pstate->numWorkers; i++)
		closesocket(pstate->parallelSlot[i].pipeWrite);

	/*
	 * Force early termination of any commands currently in progress.
	 */
#ifndef WIN32
	/* On non-Windows, send SIGTERM to each worker process. */
	for (i = 0; i < pstate->numWorkers; i++)
	{
		pid_t		pid = pstate->parallelSlot[i].pid;

		if (pid != 0)
			kill(pid, SIGTERM);
	}
#else

	/*
	 * On Windows, send query cancels directly to the workers' backends.  Use
	 * a critical section to ensure worker threads don't change state.
	 */
	EnterCriticalSection(&signal_info_lock);
	for (i = 0; i < pstate->numWorkers; i++)
	{
		ArchiveHandle *AH = pstate->parallelSlot[i].AH;
		char		errbuf[1];

		if (AH != NULL && AH->connCancel != NULL)
			(void) PQcancel(AH->connCancel, errbuf, sizeof(errbuf));
	}
	LeaveCriticalSection(&signal_info_lock);
#endif

	/* Now wait for them to terminate. */
	WaitForTerminatingWorkers(pstate);
}