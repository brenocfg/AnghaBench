#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_15__ {scalar_t__* count; int /*<<< orphan*/  mutex; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lockModeNames; } ;
struct TYPE_13__ {int holdMask; } ;
struct TYPE_12__ {int /*<<< orphan*/ * myProc; int /*<<< orphan*/ * myLock; } ;
typedef  TYPE_1__ PROCLOCKTAG ;
typedef  TYPE_2__ PROCLOCK ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  TYPE_3__* LockMethod ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  size_t LOCKMODE ;
typedef  int /*<<< orphan*/  LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CleanUpLock (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,size_t,int) ; 
 scalar_t__ ConflictsWithRelationFastPath (int /*<<< orphan*/ *,size_t) ; 
 size_t FastPathStrongLockHashPartition (size_t) ; 
 TYPE_9__* FastPathStrongRelationLocks ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int LOCKBIT_ON (size_t) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/ * LockHashPartitionLock (size_t) ; 
 int /*<<< orphan*/  LockMethodLockHash ; 
 int /*<<< orphan*/  LockMethodProcLockHash ; 
 size_t LockTagHashCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PROCLOCK_PRINT (char*,TYPE_2__*) ; 
 size_t ProcLockHashCode (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int UnGrantLock (int /*<<< orphan*/ *,size_t,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
LockRefindAndRelease(LockMethod lockMethodTable, PGPROC *proc,
					 LOCKTAG *locktag, LOCKMODE lockmode,
					 bool decrement_strong_lock_count)
{
	LOCK	   *lock;
	PROCLOCK   *proclock;
	PROCLOCKTAG proclocktag;
	uint32		hashcode;
	uint32		proclock_hashcode;
	LWLock	   *partitionLock;
	bool		wakeupNeeded;

	hashcode = LockTagHashCode(locktag);
	partitionLock = LockHashPartitionLock(hashcode);

	LWLockAcquire(partitionLock, LW_EXCLUSIVE);

	/*
	 * Re-find the lock object (it had better be there).
	 */
	lock = (LOCK *) hash_search_with_hash_value(LockMethodLockHash,
												(void *) locktag,
												hashcode,
												HASH_FIND,
												NULL);
	if (!lock)
		elog(PANIC, "failed to re-find shared lock object");

	/*
	 * Re-find the proclock object (ditto).
	 */
	proclocktag.myLock = lock;
	proclocktag.myProc = proc;

	proclock_hashcode = ProcLockHashCode(&proclocktag, hashcode);

	proclock = (PROCLOCK *) hash_search_with_hash_value(LockMethodProcLockHash,
														(void *) &proclocktag,
														proclock_hashcode,
														HASH_FIND,
														NULL);
	if (!proclock)
		elog(PANIC, "failed to re-find shared proclock object");

	/*
	 * Double-check that we are actually holding a lock of the type we want to
	 * release.
	 */
	if (!(proclock->holdMask & LOCKBIT_ON(lockmode)))
	{
		PROCLOCK_PRINT("lock_twophase_postcommit: WRONGTYPE", proclock);
		LWLockRelease(partitionLock);
		elog(WARNING, "you don't own a lock of type %s",
			 lockMethodTable->lockModeNames[lockmode]);
		return;
	}

	/*
	 * Do the releasing.  CleanUpLock will waken any now-wakable waiters.
	 */
	wakeupNeeded = UnGrantLock(lock, lockmode, proclock, lockMethodTable);

	CleanUpLock(lock, proclock,
				lockMethodTable, hashcode,
				wakeupNeeded);

	LWLockRelease(partitionLock);

	/*
	 * Decrement strong lock count.  This logic is needed only for 2PC.
	 */
	if (decrement_strong_lock_count
		&& ConflictsWithRelationFastPath(locktag, lockmode))
	{
		uint32		fasthashcode = FastPathStrongLockHashPartition(hashcode);

		SpinLockAcquire(&FastPathStrongRelationLocks->mutex);
		Assert(FastPathStrongRelationLocks->count[fasthashcode] > 0);
		FastPathStrongRelationLocks->count[fasthashcode]--;
		SpinLockRelease(&FastPathStrongRelationLocks->mutex);
	}
}