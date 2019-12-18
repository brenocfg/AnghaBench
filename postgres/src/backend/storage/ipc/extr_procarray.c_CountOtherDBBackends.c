#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ databaseId; int pid; } ;
struct TYPE_9__ {int vacuumFlags; } ;
struct TYPE_8__ {int numProcs; int* pgprocnos; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGXACT ;
typedef  TYPE_3__ PGPROC ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int MAXAUTOVACPIDS ; 
 TYPE_3__* MyProc ; 
 int PROC_IS_AUTOVACUUM ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  SIGTERM ; 
 TYPE_2__* allPgXact ; 
 TYPE_3__* allProcs ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_usleep (int) ; 
 TYPE_1__* procArray ; 

bool
CountOtherDBBackends(Oid databaseId, int *nbackends, int *nprepared)
{
	ProcArrayStruct *arrayP = procArray;

#define MAXAUTOVACPIDS	10		/* max autovacs to SIGTERM per iteration */
	int			autovac_pids[MAXAUTOVACPIDS];
	int			tries;

	/* 50 tries with 100ms sleep between tries makes 5 sec total wait */
	for (tries = 0; tries < 50; tries++)
	{
		int			nautovacs = 0;
		bool		found = false;
		int			index;

		CHECK_FOR_INTERRUPTS();

		*nbackends = *nprepared = 0;

		LWLockAcquire(ProcArrayLock, LW_SHARED);

		for (index = 0; index < arrayP->numProcs; index++)
		{
			int			pgprocno = arrayP->pgprocnos[index];
			PGPROC	   *proc = &allProcs[pgprocno];
			PGXACT	   *pgxact = &allPgXact[pgprocno];

			if (proc->databaseId != databaseId)
				continue;
			if (proc == MyProc)
				continue;

			found = true;

			if (proc->pid == 0)
				(*nprepared)++;
			else
			{
				(*nbackends)++;
				if ((pgxact->vacuumFlags & PROC_IS_AUTOVACUUM) &&
					nautovacs < MAXAUTOVACPIDS)
					autovac_pids[nautovacs++] = proc->pid;
			}
		}

		LWLockRelease(ProcArrayLock);

		if (!found)
			return false;		/* no conflicting backends, so done */

		/*
		 * Send SIGTERM to any conflicting autovacuums before sleeping. We
		 * postpone this step until after the loop because we don't want to
		 * hold ProcArrayLock while issuing kill(). We have no idea what might
		 * block kill() inside the kernel...
		 */
		for (index = 0; index < nautovacs; index++)
			(void) kill(autovac_pids[index], SIGTERM);	/* ignore any error */

		/* sleep, then try again */
		pg_usleep(100 * 1000L); /* 100ms */
	}

	return true;				/* timed out, still conflicts */
}