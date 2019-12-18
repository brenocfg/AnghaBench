#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_9__ {scalar_t__ nRequested; int /*<<< orphan*/  tag; int /*<<< orphan*/  procLocks; } ;
struct TYPE_8__ {scalar_t__ holdMask; int /*<<< orphan*/  tag; int /*<<< orphan*/  procLink; int /*<<< orphan*/  lockLink; } ;
typedef  TYPE_1__ PROCLOCK ;
typedef  int /*<<< orphan*/  LockMethod ;
typedef  TYPE_2__ LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  LOCK_PRINT (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockMethodLockHash ; 
 int /*<<< orphan*/  LockMethodProcLockHash ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PROCLOCK_PRINT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ProcLockHashCode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcLockWakeup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SHMQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMQueueEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_search_with_hash_value (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CleanUpLock(LOCK *lock, PROCLOCK *proclock,
			LockMethod lockMethodTable, uint32 hashcode,
			bool wakeupNeeded)
{
	/*
	 * If this was my last hold on this lock, delete my entry in the proclock
	 * table.
	 */
	if (proclock->holdMask == 0)
	{
		uint32		proclock_hashcode;

		PROCLOCK_PRINT("CleanUpLock: deleting", proclock);
		SHMQueueDelete(&proclock->lockLink);
		SHMQueueDelete(&proclock->procLink);
		proclock_hashcode = ProcLockHashCode(&proclock->tag, hashcode);
		if (!hash_search_with_hash_value(LockMethodProcLockHash,
										 (void *) &(proclock->tag),
										 proclock_hashcode,
										 HASH_REMOVE,
										 NULL))
			elog(PANIC, "proclock table corrupted");
	}

	if (lock->nRequested == 0)
	{
		/*
		 * The caller just released the last lock, so garbage-collect the lock
		 * object.
		 */
		LOCK_PRINT("CleanUpLock: deleting", lock, 0);
		Assert(SHMQueueEmpty(&(lock->procLocks)));
		if (!hash_search_with_hash_value(LockMethodLockHash,
										 (void *) &(lock->tag),
										 hashcode,
										 HASH_REMOVE,
										 NULL))
			elog(PANIC, "lock table corrupted");
	}
	else if (wakeupNeeded)
	{
		/* There are waiters on this lock, so wake them up. */
		ProcLockWakeup(lockMethodTable, lock);
	}
}