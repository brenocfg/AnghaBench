#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_17__ {int /*<<< orphan*/  localTransactionId; int /*<<< orphan*/  backendId; } ;
typedef  TYPE_3__ VirtualTransactionId ;
struct TYPE_22__ {int /*<<< orphan*/  tag; } ;
struct TYPE_21__ {int nelements; TYPE_6__* locks; } ;
struct TYPE_20__ {int fastpath; int /*<<< orphan*/  leaderPid; int /*<<< orphan*/  pid; int /*<<< orphan*/  lxid; int /*<<< orphan*/  backend; void* waitLockMode; scalar_t__ holdMask; int /*<<< orphan*/  locktag; } ;
struct TYPE_19__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  lxid; int /*<<< orphan*/  backendId; void* waitLockMode; TYPE_8__* waitLock; int /*<<< orphan*/  backendLock; int /*<<< orphan*/  fpLocalTransactionId; scalar_t__ fpVXIDLock; int /*<<< orphan*/ * fpRelId; int /*<<< orphan*/  databaseId; } ;
struct TYPE_16__ {TYPE_8__* myLock; TYPE_5__* myProc; } ;
struct TYPE_18__ {TYPE_1__* groupLeader; TYPE_2__ tag; scalar_t__ holdMask; } ;
struct TYPE_15__ {int /*<<< orphan*/  pid; } ;
struct TYPE_14__ {int allProcCount; TYPE_5__* allProcs; } ;
typedef  TYPE_4__ PROCLOCK ;
typedef  TYPE_5__ PGPROC ;
typedef  TYPE_6__ LockInstanceData ;
typedef  TYPE_7__ LockData ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  TYPE_8__ LOCK ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ FAST_PATH_GET_BITS (TYPE_5__*,scalar_t__) ; 
 scalar_t__ FAST_PATH_LOCKNUMBER_OFFSET ; 
 scalar_t__ FP_LOCK_SLOTS_PER_BACKEND ; 
 scalar_t__ LOCKBIT_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/ * LockHashPartitionLockByIndex (int) ; 
 int /*<<< orphan*/  LockMethodProcLockHash ; 
 int MaxBackends ; 
 int NUM_LOCK_PARTITIONS ; 
 void* NoLock ; 
 TYPE_11__* ProcGlobal ; 
 int /*<<< orphan*/  SET_LOCKTAG_RELATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_LOCKTAG_VIRTUALTRANSACTION (int /*<<< orphan*/ ,TYPE_3__) ; 
 int hash_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ repalloc (TYPE_6__*,int) ; 

LockData *
GetLockStatusData(void)
{
	LockData   *data;
	PROCLOCK   *proclock;
	HASH_SEQ_STATUS seqstat;
	int			els;
	int			el;
	int			i;

	data = (LockData *) palloc(sizeof(LockData));

	/* Guess how much space we'll need. */
	els = MaxBackends;
	el = 0;
	data->locks = (LockInstanceData *) palloc(sizeof(LockInstanceData) * els);

	/*
	 * First, we iterate through the per-backend fast-path arrays, locking
	 * them one at a time.  This might produce an inconsistent picture of the
	 * system state, but taking all of those LWLocks at the same time seems
	 * impractical (in particular, note MAX_SIMUL_LWLOCKS).  It shouldn't
	 * matter too much, because none of these locks can be involved in lock
	 * conflicts anyway - anything that might must be present in the main lock
	 * table.  (For the same reason, we don't sweat about making leaderPid
	 * completely valid.  We cannot safely dereference another backend's
	 * lockGroupLeader field without holding all lock partition locks, and
	 * it's not worth that.)
	 */
	for (i = 0; i < ProcGlobal->allProcCount; ++i)
	{
		PGPROC	   *proc = &ProcGlobal->allProcs[i];
		uint32		f;

		LWLockAcquire(&proc->backendLock, LW_SHARED);

		for (f = 0; f < FP_LOCK_SLOTS_PER_BACKEND; ++f)
		{
			LockInstanceData *instance;
			uint32		lockbits = FAST_PATH_GET_BITS(proc, f);

			/* Skip unallocated slots. */
			if (!lockbits)
				continue;

			if (el >= els)
			{
				els += MaxBackends;
				data->locks = (LockInstanceData *)
					repalloc(data->locks, sizeof(LockInstanceData) * els);
			}

			instance = &data->locks[el];
			SET_LOCKTAG_RELATION(instance->locktag, proc->databaseId,
								 proc->fpRelId[f]);
			instance->holdMask = lockbits << FAST_PATH_LOCKNUMBER_OFFSET;
			instance->waitLockMode = NoLock;
			instance->backend = proc->backendId;
			instance->lxid = proc->lxid;
			instance->pid = proc->pid;
			instance->leaderPid = proc->pid;
			instance->fastpath = true;

			el++;
		}

		if (proc->fpVXIDLock)
		{
			VirtualTransactionId vxid;
			LockInstanceData *instance;

			if (el >= els)
			{
				els += MaxBackends;
				data->locks = (LockInstanceData *)
					repalloc(data->locks, sizeof(LockInstanceData) * els);
			}

			vxid.backendId = proc->backendId;
			vxid.localTransactionId = proc->fpLocalTransactionId;

			instance = &data->locks[el];
			SET_LOCKTAG_VIRTUALTRANSACTION(instance->locktag, vxid);
			instance->holdMask = LOCKBIT_ON(ExclusiveLock);
			instance->waitLockMode = NoLock;
			instance->backend = proc->backendId;
			instance->lxid = proc->lxid;
			instance->pid = proc->pid;
			instance->leaderPid = proc->pid;
			instance->fastpath = true;

			el++;
		}

		LWLockRelease(&proc->backendLock);
	}

	/*
	 * Next, acquire lock on the entire shared lock data structure.  We do
	 * this so that, at least for locks in the primary lock table, the state
	 * will be self-consistent.
	 *
	 * Since this is a read-only operation, we take shared instead of
	 * exclusive lock.  There's not a whole lot of point to this, because all
	 * the normal operations require exclusive lock, but it doesn't hurt
	 * anything either. It will at least allow two backends to do
	 * GetLockStatusData in parallel.
	 *
	 * Must grab LWLocks in partition-number order to avoid LWLock deadlock.
	 */
	for (i = 0; i < NUM_LOCK_PARTITIONS; i++)
		LWLockAcquire(LockHashPartitionLockByIndex(i), LW_SHARED);

	/* Now we can safely count the number of proclocks */
	data->nelements = el + hash_get_num_entries(LockMethodProcLockHash);
	if (data->nelements > els)
	{
		els = data->nelements;
		data->locks = (LockInstanceData *)
			repalloc(data->locks, sizeof(LockInstanceData) * els);
	}

	/* Now scan the tables to copy the data */
	hash_seq_init(&seqstat, LockMethodProcLockHash);

	while ((proclock = (PROCLOCK *) hash_seq_search(&seqstat)))
	{
		PGPROC	   *proc = proclock->tag.myProc;
		LOCK	   *lock = proclock->tag.myLock;
		LockInstanceData *instance = &data->locks[el];

		memcpy(&instance->locktag, &lock->tag, sizeof(LOCKTAG));
		instance->holdMask = proclock->holdMask;
		if (proc->waitLock == proclock->tag.myLock)
			instance->waitLockMode = proc->waitLockMode;
		else
			instance->waitLockMode = NoLock;
		instance->backend = proc->backendId;
		instance->lxid = proc->lxid;
		instance->pid = proc->pid;
		instance->leaderPid = proclock->groupLeader->pid;
		instance->fastpath = false;

		el++;
	}

	/*
	 * And release locks.  We do this in reverse order for two reasons: (1)
	 * Anyone else who needs more than one of the locks will be trying to lock
	 * them in increasing order; we don't want to release the other process
	 * until it can get all the locks it needs. (2) This avoids O(N^2)
	 * behavior inside LWLockRelease.
	 */
	for (i = NUM_LOCK_PARTITIONS; --i >= 0;)
		LWLockRelease(LockHashPartitionLockByIndex(i));

	Assert(el == data->nelements);

	return data;
}