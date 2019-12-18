#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  relOid; int /*<<< orphan*/  dbOid; int /*<<< orphan*/  xid; } ;
typedef  TYPE_3__ xl_standby_lock ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_18__ {TYPE_5__* allPgXact; } ;
struct TYPE_12__ {scalar_t__ locktag_type; int /*<<< orphan*/  locktag_field2; int /*<<< orphan*/  locktag_field1; } ;
struct TYPE_17__ {TYPE_2__ tag; } ;
struct TYPE_16__ {size_t pgprocno; } ;
struct TYPE_15__ {int /*<<< orphan*/  xid; } ;
struct TYPE_11__ {TYPE_7__* myLock; TYPE_6__* myProc; } ;
struct TYPE_14__ {int holdMask; TYPE_1__ tag; } ;
typedef  TYPE_4__ PROCLOCK ;
typedef  TYPE_5__ PGXACT ;
typedef  TYPE_6__ PGPROC ;
typedef  TYPE_7__ LOCK ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int LOCKBIT_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ LOCKTAG_RELATION ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  LockHashPartitionLockByIndex (int) ; 
 int /*<<< orphan*/  LockMethodProcLockHash ; 
 int NUM_LOCK_PARTITIONS ; 
 TYPE_9__* ProcGlobal ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int hash_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 TYPE_3__* palloc (int) ; 

xl_standby_lock *
GetRunningTransactionLocks(int *nlocks)
{
	xl_standby_lock *accessExclusiveLocks;
	PROCLOCK   *proclock;
	HASH_SEQ_STATUS seqstat;
	int			i;
	int			index;
	int			els;

	/*
	 * Acquire lock on the entire shared lock data structure.
	 *
	 * Must grab LWLocks in partition-number order to avoid LWLock deadlock.
	 */
	for (i = 0; i < NUM_LOCK_PARTITIONS; i++)
		LWLockAcquire(LockHashPartitionLockByIndex(i), LW_SHARED);

	/* Now we can safely count the number of proclocks */
	els = hash_get_num_entries(LockMethodProcLockHash);

	/*
	 * Allocating enough space for all locks in the lock table is overkill,
	 * but it's more convenient and faster than having to enlarge the array.
	 */
	accessExclusiveLocks = palloc(els * sizeof(xl_standby_lock));

	/* Now scan the tables to copy the data */
	hash_seq_init(&seqstat, LockMethodProcLockHash);

	/*
	 * If lock is a currently granted AccessExclusiveLock then it will have
	 * just one proclock holder, so locks are never accessed twice in this
	 * particular case. Don't copy this code for use elsewhere because in the
	 * general case this will give you duplicate locks when looking at
	 * non-exclusive lock types.
	 */
	index = 0;
	while ((proclock = (PROCLOCK *) hash_seq_search(&seqstat)))
	{
		/* make sure this definition matches the one used in LockAcquire */
		if ((proclock->holdMask & LOCKBIT_ON(AccessExclusiveLock)) &&
			proclock->tag.myLock->tag.locktag_type == LOCKTAG_RELATION)
		{
			PGPROC	   *proc = proclock->tag.myProc;
			PGXACT	   *pgxact = &ProcGlobal->allPgXact[proc->pgprocno];
			LOCK	   *lock = proclock->tag.myLock;
			TransactionId xid = pgxact->xid;

			/*
			 * Don't record locks for transactions if we know they have
			 * already issued their WAL record for commit but not yet released
			 * lock. It is still possible that we see locks held by already
			 * complete transactions, if they haven't yet zeroed their xids.
			 */
			if (!TransactionIdIsValid(xid))
				continue;

			accessExclusiveLocks[index].xid = xid;
			accessExclusiveLocks[index].dbOid = lock->tag.locktag_field1;
			accessExclusiveLocks[index].relOid = lock->tag.locktag_field2;

			index++;
		}
	}

	Assert(index <= els);

	/*
	 * And release locks.  We do this in reverse order for two reasons: (1)
	 * Anyone else who needs more than one of the locks will be trying to lock
	 * them in increasing order; we don't want to release the other process
	 * until it can get all the locks it needs. (2) This avoids O(N^2)
	 * behavior inside LWLockRelease.
	 */
	for (i = NUM_LOCK_PARTITIONS; --i >= 0;)
		LWLockRelease(LockHashPartitionLockByIndex(i));

	*nlocks = index;
	return accessExclusiveLocks;
}