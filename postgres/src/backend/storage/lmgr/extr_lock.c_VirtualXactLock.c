#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_13__ {scalar_t__ backendId; scalar_t__ localTransactionId; } ;
typedef  TYPE_2__ VirtualTransactionId ;
struct TYPE_15__ {scalar_t__ backendId; scalar_t__ fpLocalTransactionId; int fpVXIDLock; int /*<<< orphan*/  backendLock; } ;
struct TYPE_12__ {int /*<<< orphan*/  myLock; } ;
struct TYPE_14__ {TYPE_1__ tag; } ;
typedef  TYPE_3__ PROCLOCK ;
typedef  TYPE_4__ PGPROC ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* BackendIdGetProc (scalar_t__) ; 
 size_t DEFAULT_LOCKMETHOD ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  GrantLock (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * LockHashPartitionLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LockMethods ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LockTagHashCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_LOCKTAG_VIRTUALTRANSACTION (int /*<<< orphan*/ ,TYPE_2__) ; 
 TYPE_3__* SetupLockInTable (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  VirtualTransactionIdIsValid (TYPE_2__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

bool
VirtualXactLock(VirtualTransactionId vxid, bool wait)
{
	LOCKTAG		tag;
	PGPROC	   *proc;

	Assert(VirtualTransactionIdIsValid(vxid));

	SET_LOCKTAG_VIRTUALTRANSACTION(tag, vxid);

	/*
	 * If a lock table entry must be made, this is the PGPROC on whose behalf
	 * it must be done.  Note that the transaction might end or the PGPROC
	 * might be reassigned to a new backend before we get around to examining
	 * it, but it doesn't matter.  If we find upon examination that the
	 * relevant lxid is no longer running here, that's enough to prove that
	 * it's no longer running anywhere.
	 */
	proc = BackendIdGetProc(vxid.backendId);
	if (proc == NULL)
		return true;

	/*
	 * We must acquire this lock before checking the backendId and lxid
	 * against the ones we're waiting for.  The target backend will only set
	 * or clear lxid while holding this lock.
	 */
	LWLockAcquire(&proc->backendLock, LW_EXCLUSIVE);

	/* If the transaction has ended, our work here is done. */
	if (proc->backendId != vxid.backendId
		|| proc->fpLocalTransactionId != vxid.localTransactionId)
	{
		LWLockRelease(&proc->backendLock);
		return true;
	}

	/*
	 * If we aren't asked to wait, there's no need to set up a lock table
	 * entry.  The transaction is still in progress, so just return false.
	 */
	if (!wait)
	{
		LWLockRelease(&proc->backendLock);
		return false;
	}

	/*
	 * OK, we're going to need to sleep on the VXID.  But first, we must set
	 * up the primary lock table entry, if needed (ie, convert the proc's
	 * fast-path lock on its VXID to a regular lock).
	 */
	if (proc->fpVXIDLock)
	{
		PROCLOCK   *proclock;
		uint32		hashcode;
		LWLock	   *partitionLock;

		hashcode = LockTagHashCode(&tag);

		partitionLock = LockHashPartitionLock(hashcode);
		LWLockAcquire(partitionLock, LW_EXCLUSIVE);

		proclock = SetupLockInTable(LockMethods[DEFAULT_LOCKMETHOD], proc,
									&tag, hashcode, ExclusiveLock);
		if (!proclock)
		{
			LWLockRelease(partitionLock);
			LWLockRelease(&proc->backendLock);
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of shared memory"),
					 errhint("You might need to increase max_locks_per_transaction.")));
		}
		GrantLock(proclock->tag.myLock, proclock, ExclusiveLock);

		LWLockRelease(partitionLock);

		proc->fpVXIDLock = false;
	}

	/* Done with proc->fpLockBits */
	LWLockRelease(&proc->backendLock);

	/* Time to wait. */
	(void) LockAcquire(&tag, ShareLock, false, false);

	LockRelease(&tag, ShareLock, false);
	return true;
}