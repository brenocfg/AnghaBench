#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ next; } ;
struct TYPE_16__ {int size; TYPE_1__ links; } ;
struct TYPE_19__ {TYPE_3__ waitProcs; } ;
struct TYPE_18__ {int* conflictTab; } ;
struct TYPE_15__ {scalar_t__ next; } ;
struct TYPE_17__ {size_t waitLockMode; TYPE_2__ links; int /*<<< orphan*/  waitProcLock; } ;
typedef  TYPE_3__ PROC_QUEUE ;
typedef  TYPE_4__ PGPROC ;
typedef  TYPE_5__* LockMethod ;
typedef  size_t LOCKMODE ;
typedef  int LOCKMASK ;
typedef  TYPE_6__ LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GrantLock (TYPE_6__*,int /*<<< orphan*/ ,size_t) ; 
 int LOCKBIT_ON (size_t) ; 
 scalar_t__ LockCheckConflicts (TYPE_5__*,size_t,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ProcWakeup (TYPE_4__*,scalar_t__) ; 
 scalar_t__ STATUS_OK ; 

void
ProcLockWakeup(LockMethod lockMethodTable, LOCK *lock)
{
	PROC_QUEUE *waitQueue = &(lock->waitProcs);
	int			queue_size = waitQueue->size;
	PGPROC	   *proc;
	LOCKMASK	aheadRequests = 0;

	Assert(queue_size >= 0);

	if (queue_size == 0)
		return;

	proc = (PGPROC *) waitQueue->links.next;

	while (queue_size-- > 0)
	{
		LOCKMODE	lockmode = proc->waitLockMode;

		/*
		 * Waken if (a) doesn't conflict with requests of earlier waiters, and
		 * (b) doesn't conflict with already-held locks.
		 */
		if ((lockMethodTable->conflictTab[lockmode] & aheadRequests) == 0 &&
			LockCheckConflicts(lockMethodTable,
							   lockmode,
							   lock,
							   proc->waitProcLock) == STATUS_OK)
		{
			/* OK to waken */
			GrantLock(lock, proc->waitProcLock, lockmode);
			proc = ProcWakeup(proc, STATUS_OK);

			/*
			 * ProcWakeup removes proc from the lock's waiting process queue
			 * and returns the next proc in chain; don't use proc's next-link,
			 * because it's been cleared.
			 */
		}
		else
		{
			/*
			 * Cannot wake this guy. Remember his request for later checks.
			 */
			aheadRequests |= LOCKBIT_ON(lockmode);
			proc = (PGPROC *) proc->links.next;
		}
	}

	Assert(waitQueue->size >= 0);
}