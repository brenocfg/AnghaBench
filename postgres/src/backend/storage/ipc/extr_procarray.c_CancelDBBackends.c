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
typedef  scalar_t__ pid_t ;
struct TYPE_8__ {int /*<<< orphan*/  backendId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
struct TYPE_10__ {scalar_t__ databaseId; int recoveryConflictPending; scalar_t__ pid; } ;
struct TYPE_9__ {int numProcs; int* pgprocnos; } ;
typedef  int /*<<< orphan*/  ProcSignalReason ;
typedef  TYPE_2__ ProcArrayStruct ;
typedef  TYPE_3__ PGPROC ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  GET_VXID_FROM_PGPROC (TYPE_1__,TYPE_3__) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  SendProcSignal (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* allProcs ; 
 TYPE_2__* procArray ; 

void
CancelDBBackends(Oid databaseid, ProcSignalReason sigmode, bool conflictPending)
{
	ProcArrayStruct *arrayP = procArray;
	int			index;
	pid_t		pid = 0;

	/* tell all backends to die */
	LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);

	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		PGPROC	   *proc = &allProcs[pgprocno];

		if (databaseid == InvalidOid || proc->databaseId == databaseid)
		{
			VirtualTransactionId procvxid;

			GET_VXID_FROM_PGPROC(procvxid, *proc);

			proc->recoveryConflictPending = conflictPending;
			pid = proc->pid;
			if (pid != 0)
			{
				/*
				 * Kill the pid if it's still here. If not, that's what we
				 * wanted so ignore any errors.
				 */
				(void) SendProcSignal(pid, sigmode, procvxid.backendId);
			}
		}
	}

	LWLockRelease(ProcArrayLock);
}