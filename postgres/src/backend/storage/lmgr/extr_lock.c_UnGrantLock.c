#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ nRequested; scalar_t__* requested; scalar_t__ nGranted; scalar_t__* granted; int waitMask; int /*<<< orphan*/  grantMask; } ;
struct TYPE_10__ {int* conflictTab; } ;
struct TYPE_9__ {int /*<<< orphan*/  holdMask; } ;
typedef  TYPE_1__ PROCLOCK ;
typedef  TYPE_2__* LockMethod ;
typedef  size_t LOCKMODE ;
typedef  TYPE_3__ LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LOCKBIT_OFF (size_t) ; 
 int /*<<< orphan*/  LOCK_PRINT (char*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  PROCLOCK_PRINT (char*,TYPE_1__*) ; 

__attribute__((used)) static bool
UnGrantLock(LOCK *lock, LOCKMODE lockmode,
			PROCLOCK *proclock, LockMethod lockMethodTable)
{
	bool		wakeupNeeded = false;

	Assert((lock->nRequested > 0) && (lock->requested[lockmode] > 0));
	Assert((lock->nGranted > 0) && (lock->granted[lockmode] > 0));
	Assert(lock->nGranted <= lock->nRequested);

	/*
	 * fix the general lock stats
	 */
	lock->nRequested--;
	lock->requested[lockmode]--;
	lock->nGranted--;
	lock->granted[lockmode]--;

	if (lock->granted[lockmode] == 0)
	{
		/* change the conflict mask.  No more of this lock type. */
		lock->grantMask &= LOCKBIT_OFF(lockmode);
	}

	LOCK_PRINT("UnGrantLock: updated", lock, lockmode);

	/*
	 * We need only run ProcLockWakeup if the released lock conflicts with at
	 * least one of the lock types requested by waiter(s).  Otherwise whatever
	 * conflict made them wait must still exist.  NOTE: before MVCC, we could
	 * skip wakeup if lock->granted[lockmode] was still positive. But that's
	 * not true anymore, because the remaining granted locks might belong to
	 * some waiter, who could now be awakened because he doesn't conflict with
	 * his own locks.
	 */
	if (lockMethodTable->conflictTab[lockmode] & lock->waitMask)
		wakeupNeeded = true;

	/*
	 * Now fix the per-proclock state.
	 */
	proclock->holdMask &= LOCKBIT_OFF(lockmode);
	PROCLOCK_PRINT("UnGrantLock: updated", proclock);

	return wakeupNeeded;
}