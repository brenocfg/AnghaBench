#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  localtag ;
struct TYPE_29__ {scalar_t__ nLocks; int numLockOwners; int lockCleared; int /*<<< orphan*/  hashcode; TYPE_2__* proclock; int /*<<< orphan*/ * lock; TYPE_6__* lockOwners; } ;
struct TYPE_28__ {scalar_t__ nLocks; int /*<<< orphan*/ * owner; } ;
struct TYPE_26__ {size_t locktag_lockmethodid; int /*<<< orphan*/  locktag_field2; int /*<<< orphan*/  locktag_field1; } ;
struct TYPE_27__ {size_t mode; TYPE_4__ lock; } ;
struct TYPE_25__ {size_t numLockModes; size_t* lockModeNames; } ;
struct TYPE_24__ {int holdMask; } ;
struct TYPE_23__ {TYPE_14__* myProc; int /*<<< orphan*/ * myLock; } ;
struct TYPE_22__ {int /*<<< orphan*/  backendLock; } ;
typedef  int /*<<< orphan*/ * ResourceOwner ;
typedef  TYPE_1__ PROCLOCKTAG ;
typedef  TYPE_2__ PROCLOCK ;
typedef  TYPE_3__* LockMethod ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  TYPE_4__ LOCKTAG ;
typedef  size_t LOCKMODE ;
typedef  size_t LOCKMETHODID ;
typedef  int /*<<< orphan*/  LOCK ;
typedef  TYPE_5__ LOCALLOCKTAG ;
typedef  TYPE_6__ LOCALLOCKOWNER ;
typedef  TYPE_7__ LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CleanUpLock (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int EligibleForRelationFastPath (TYPE_4__ const*,size_t) ; 
 scalar_t__ FastPathLocalUseCount ; 
 int FastPathUnGrantRelationLock (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int LOCKBIT_ON (size_t) ; 
 scalar_t__ LOCK_DEBUG_ENABLED (TYPE_4__ const*) ; 
 int /*<<< orphan*/  LOCK_PRINT (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/ * LockHashPartitionLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockMethodLocalHash ; 
 int /*<<< orphan*/  LockMethodLockHash ; 
 int /*<<< orphan*/  LockMethodProcLockHash ; 
 TYPE_3__** LockMethods ; 
 int /*<<< orphan*/  MemSet (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 TYPE_14__* MyProc ; 
 int /*<<< orphan*/  PROCLOCK_PRINT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  RemoveLocalLock (TYPE_7__*) ; 
 int /*<<< orphan*/  ResourceOwnerForgetLock (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int UnGrantLock (int /*<<< orphan*/ *,size_t,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t lengthof (TYPE_3__**) ; 

bool
LockRelease(const LOCKTAG *locktag, LOCKMODE lockmode, bool sessionLock)
{
	LOCKMETHODID lockmethodid = locktag->locktag_lockmethodid;
	LockMethod	lockMethodTable;
	LOCALLOCKTAG localtag;
	LOCALLOCK  *locallock;
	LOCK	   *lock;
	PROCLOCK   *proclock;
	LWLock	   *partitionLock;
	bool		wakeupNeeded;

	if (lockmethodid <= 0 || lockmethodid >= lengthof(LockMethods))
		elog(ERROR, "unrecognized lock method: %d", lockmethodid);
	lockMethodTable = LockMethods[lockmethodid];
	if (lockmode <= 0 || lockmode > lockMethodTable->numLockModes)
		elog(ERROR, "unrecognized lock mode: %d", lockmode);

#ifdef LOCK_DEBUG
	if (LOCK_DEBUG_ENABLED(locktag))
		elog(LOG, "LockRelease: lock [%u,%u] %s",
			 locktag->locktag_field1, locktag->locktag_field2,
			 lockMethodTable->lockModeNames[lockmode]);
#endif

	/*
	 * Find the LOCALLOCK entry for this lock and lockmode
	 */
	MemSet(&localtag, 0, sizeof(localtag)); /* must clear padding */
	localtag.lock = *locktag;
	localtag.mode = lockmode;

	locallock = (LOCALLOCK *) hash_search(LockMethodLocalHash,
										  (void *) &localtag,
										  HASH_FIND, NULL);

	/*
	 * let the caller print its own error message, too. Do not ereport(ERROR).
	 */
	if (!locallock || locallock->nLocks <= 0)
	{
		elog(WARNING, "you don't own a lock of type %s",
			 lockMethodTable->lockModeNames[lockmode]);
		return false;
	}

	/*
	 * Decrease the count for the resource owner.
	 */
	{
		LOCALLOCKOWNER *lockOwners = locallock->lockOwners;
		ResourceOwner owner;
		int			i;

		/* Identify owner for lock */
		if (sessionLock)
			owner = NULL;
		else
			owner = CurrentResourceOwner;

		for (i = locallock->numLockOwners - 1; i >= 0; i--)
		{
			if (lockOwners[i].owner == owner)
			{
				Assert(lockOwners[i].nLocks > 0);
				if (--lockOwners[i].nLocks == 0)
				{
					if (owner != NULL)
						ResourceOwnerForgetLock(owner, locallock);
					/* compact out unused slot */
					locallock->numLockOwners--;
					if (i < locallock->numLockOwners)
						lockOwners[i] = lockOwners[locallock->numLockOwners];
				}
				break;
			}
		}
		if (i < 0)
		{
			/* don't release a lock belonging to another owner */
			elog(WARNING, "you don't own a lock of type %s",
				 lockMethodTable->lockModeNames[lockmode]);
			return false;
		}
	}

	/*
	 * Decrease the total local count.  If we're still holding the lock, we're
	 * done.
	 */
	locallock->nLocks--;

	if (locallock->nLocks > 0)
		return true;

	/*
	 * At this point we can no longer suppose we are clear of invalidation
	 * messages related to this lock.  Although we'll delete the LOCALLOCK
	 * object before any intentional return from this routine, it seems worth
	 * the trouble to explicitly reset lockCleared right now, just in case
	 * some error prevents us from deleting the LOCALLOCK.
	 */
	locallock->lockCleared = false;

	/* Attempt fast release of any lock eligible for the fast path. */
	if (EligibleForRelationFastPath(locktag, lockmode) &&
		FastPathLocalUseCount > 0)
	{
		bool		released;

		/*
		 * We might not find the lock here, even if we originally entered it
		 * here.  Another backend may have moved it to the main table.
		 */
		LWLockAcquire(&MyProc->backendLock, LW_EXCLUSIVE);
		released = FastPathUnGrantRelationLock(locktag->locktag_field2,
											   lockmode);
		LWLockRelease(&MyProc->backendLock);
		if (released)
		{
			RemoveLocalLock(locallock);
			return true;
		}
	}

	/*
	 * Otherwise we've got to mess with the shared lock table.
	 */
	partitionLock = LockHashPartitionLock(locallock->hashcode);

	LWLockAcquire(partitionLock, LW_EXCLUSIVE);

	/*
	 * Normally, we don't need to re-find the lock or proclock, since we kept
	 * their addresses in the locallock table, and they couldn't have been
	 * removed while we were holding a lock on them.  But it's possible that
	 * the lock was taken fast-path and has since been moved to the main hash
	 * table by another backend, in which case we will need to look up the
	 * objects here.  We assume the lock field is NULL if so.
	 */
	lock = locallock->lock;
	if (!lock)
	{
		PROCLOCKTAG proclocktag;

		Assert(EligibleForRelationFastPath(locktag, lockmode));
		lock = (LOCK *) hash_search_with_hash_value(LockMethodLockHash,
													(const void *) locktag,
													locallock->hashcode,
													HASH_FIND,
													NULL);
		if (!lock)
			elog(ERROR, "failed to re-find shared lock object");
		locallock->lock = lock;

		proclocktag.myLock = lock;
		proclocktag.myProc = MyProc;
		locallock->proclock = (PROCLOCK *) hash_search(LockMethodProcLockHash,
													   (void *) &proclocktag,
													   HASH_FIND,
													   NULL);
		if (!locallock->proclock)
			elog(ERROR, "failed to re-find shared proclock object");
	}
	LOCK_PRINT("LockRelease: found", lock, lockmode);
	proclock = locallock->proclock;
	PROCLOCK_PRINT("LockRelease: found", proclock);

	/*
	 * Double-check that we are actually holding a lock of the type we want to
	 * release.
	 */
	if (!(proclock->holdMask & LOCKBIT_ON(lockmode)))
	{
		PROCLOCK_PRINT("LockRelease: WRONGTYPE", proclock);
		LWLockRelease(partitionLock);
		elog(WARNING, "you don't own a lock of type %s",
			 lockMethodTable->lockModeNames[lockmode]);
		RemoveLocalLock(locallock);
		return false;
	}

	/*
	 * Do the releasing.  CleanUpLock will waken any now-wakable waiters.
	 */
	wakeupNeeded = UnGrantLock(lock, lockmode, proclock, lockMethodTable);

	CleanUpLock(lock, proclock,
				lockMethodTable, locallock->hashcode,
				wakeupNeeded);

	LWLockRelease(partitionLock);

	RemoveLocalLock(locallock);
	return true;
}