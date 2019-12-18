#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_18__ {size_t allProcCount; TYPE_3__* allProcs; } ;
struct TYPE_17__ {scalar_t__ locktag_field2; scalar_t__ locktag_field1; } ;
struct TYPE_16__ {scalar_t__ databaseId; scalar_t__* fpRelId; int /*<<< orphan*/  backendLock; } ;
struct TYPE_14__ {int /*<<< orphan*/  myLock; } ;
struct TYPE_15__ {TYPE_1__ tag; } ;
typedef  TYPE_2__ PROCLOCK ;
typedef  TYPE_3__ PGPROC ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  LockMethod ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  TYPE_4__ LOCKTAG ;

/* Variables and functions */
 size_t FAST_PATH_BITS_PER_SLOT ; 
 int /*<<< orphan*/  FAST_PATH_CHECK_LOCKMODE (TYPE_3__*,size_t,size_t) ; 
 int /*<<< orphan*/  FAST_PATH_CLEAR_LOCKMODE (TYPE_3__*,size_t,size_t) ; 
 scalar_t__ FAST_PATH_GET_BITS (TYPE_3__*,size_t) ; 
 size_t FAST_PATH_LOCKNUMBER_OFFSET ; 
 size_t FP_LOCK_SLOTS_PER_BACKEND ; 
 int /*<<< orphan*/  GrantLock (int /*<<< orphan*/ ,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/ * LockHashPartitionLock (size_t) ; 
 TYPE_8__* ProcGlobal ; 
 TYPE_2__* SetupLockInTable (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__ const*,size_t,size_t) ; 

__attribute__((used)) static bool
FastPathTransferRelationLocks(LockMethod lockMethodTable, const LOCKTAG *locktag,
							  uint32 hashcode)
{
	LWLock	   *partitionLock = LockHashPartitionLock(hashcode);
	Oid			relid = locktag->locktag_field2;
	uint32		i;

	/*
	 * Every PGPROC that can potentially hold a fast-path lock is present in
	 * ProcGlobal->allProcs.  Prepared transactions are not, but any
	 * outstanding fast-path locks held by prepared transactions are
	 * transferred to the main lock table.
	 */
	for (i = 0; i < ProcGlobal->allProcCount; i++)
	{
		PGPROC	   *proc = &ProcGlobal->allProcs[i];
		uint32		f;

		LWLockAcquire(&proc->backendLock, LW_EXCLUSIVE);

		/*
		 * If the target backend isn't referencing the same database as the
		 * lock, then we needn't examine the individual relation IDs at all;
		 * none of them can be relevant.
		 *
		 * proc->databaseId is set at backend startup time and never changes
		 * thereafter, so it might be safe to perform this test before
		 * acquiring &proc->backendLock.  In particular, it's certainly safe
		 * to assume that if the target backend holds any fast-path locks, it
		 * must have performed a memory-fencing operation (in particular, an
		 * LWLock acquisition) since setting proc->databaseId.  However, it's
		 * less clear that our backend is certain to have performed a memory
		 * fencing operation since the other backend set proc->databaseId.  So
		 * for now, we test it after acquiring the LWLock just to be safe.
		 */
		if (proc->databaseId != locktag->locktag_field1)
		{
			LWLockRelease(&proc->backendLock);
			continue;
		}

		for (f = 0; f < FP_LOCK_SLOTS_PER_BACKEND; f++)
		{
			uint32		lockmode;

			/* Look for an allocated slot matching the given relid. */
			if (relid != proc->fpRelId[f] || FAST_PATH_GET_BITS(proc, f) == 0)
				continue;

			/* Find or create lock object. */
			LWLockAcquire(partitionLock, LW_EXCLUSIVE);
			for (lockmode = FAST_PATH_LOCKNUMBER_OFFSET;
				 lockmode < FAST_PATH_LOCKNUMBER_OFFSET + FAST_PATH_BITS_PER_SLOT;
				 ++lockmode)
			{
				PROCLOCK   *proclock;

				if (!FAST_PATH_CHECK_LOCKMODE(proc, f, lockmode))
					continue;
				proclock = SetupLockInTable(lockMethodTable, proc, locktag,
											hashcode, lockmode);
				if (!proclock)
				{
					LWLockRelease(partitionLock);
					LWLockRelease(&proc->backendLock);
					return false;
				}
				GrantLock(proclock->tag.myLock, proclock, lockmode);
				FAST_PATH_CLEAR_LOCKMODE(proc, f, lockmode);
			}
			LWLockRelease(partitionLock);

			/* No need to examine remaining slots. */
			break;
		}
		LWLockRelease(&proc->backendLock);
	}
	return true;
}