#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  localtag ;
struct TYPE_20__ {scalar_t__ nLocks; TYPE_1__* proclock; TYPE_4__* lock; int /*<<< orphan*/  hashcode; } ;
struct TYPE_17__ {size_t locktag_lockmethodid; int /*<<< orphan*/  locktag_field2; int /*<<< orphan*/  locktag_field1; } ;
struct TYPE_19__ {size_t mode; TYPE_3__ lock; } ;
struct TYPE_18__ {int waitMask; } ;
struct TYPE_16__ {size_t numLockModes; size_t* lockModeNames; int* conflictTab; } ;
struct TYPE_15__ {int holdMask; } ;
typedef  TYPE_1__ PROCLOCK ;
typedef  TYPE_2__* LockMethod ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  TYPE_3__ LOCKTAG ;
typedef  size_t LOCKMODE ;
typedef  size_t LOCKMETHODID ;
typedef  TYPE_4__ LOCK ;
typedef  TYPE_5__ LOCALLOCKTAG ;
typedef  TYPE_6__ LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int LOCKBIT_ON (size_t) ; 
 scalar_t__ LOCK_DEBUG_ENABLED (TYPE_3__ const*) ; 
 int /*<<< orphan*/  LOCK_PRINT (char*,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/ * LockHashPartitionLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockMethodLocalHash ; 
 TYPE_2__** LockMethods ; 
 int /*<<< orphan*/  MemSet (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PROCLOCK_PRINT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  RemoveLocalLock (TYPE_6__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,...) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t lengthof (TYPE_2__**) ; 

bool
LockHasWaiters(const LOCKTAG *locktag, LOCKMODE lockmode, bool sessionLock)
{
	LOCKMETHODID lockmethodid = locktag->locktag_lockmethodid;
	LockMethod	lockMethodTable;
	LOCALLOCKTAG localtag;
	LOCALLOCK  *locallock;
	LOCK	   *lock;
	PROCLOCK   *proclock;
	LWLock	   *partitionLock;
	bool		hasWaiters = false;

	if (lockmethodid <= 0 || lockmethodid >= lengthof(LockMethods))
		elog(ERROR, "unrecognized lock method: %d", lockmethodid);
	lockMethodTable = LockMethods[lockmethodid];
	if (lockmode <= 0 || lockmode > lockMethodTable->numLockModes)
		elog(ERROR, "unrecognized lock mode: %d", lockmode);

#ifdef LOCK_DEBUG
	if (LOCK_DEBUG_ENABLED(locktag))
		elog(LOG, "LockHasWaiters: lock [%u,%u] %s",
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
	 * Check the shared lock table.
	 */
	partitionLock = LockHashPartitionLock(locallock->hashcode);

	LWLockAcquire(partitionLock, LW_SHARED);

	/*
	 * We don't need to re-find the lock or proclock, since we kept their
	 * addresses in the locallock table, and they couldn't have been removed
	 * while we were holding a lock on them.
	 */
	lock = locallock->lock;
	LOCK_PRINT("LockHasWaiters: found", lock, lockmode);
	proclock = locallock->proclock;
	PROCLOCK_PRINT("LockHasWaiters: found", proclock);

	/*
	 * Double-check that we are actually holding a lock of the type we want to
	 * release.
	 */
	if (!(proclock->holdMask & LOCKBIT_ON(lockmode)))
	{
		PROCLOCK_PRINT("LockHasWaiters: WRONGTYPE", proclock);
		LWLockRelease(partitionLock);
		elog(WARNING, "you don't own a lock of type %s",
			 lockMethodTable->lockModeNames[lockmode]);
		RemoveLocalLock(locallock);
		return false;
	}

	/*
	 * Do the checking.
	 */
	if ((lockMethodTable->conflictTab[lockmode] & lock->waitMask) != 0)
		hasWaiters = true;

	LWLockRelease(partitionLock);

	return hasWaiters;
}