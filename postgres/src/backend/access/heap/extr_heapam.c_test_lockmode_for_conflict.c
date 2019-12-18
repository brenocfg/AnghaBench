#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {int /*<<< orphan*/  t_ctid; } ;
struct TYPE_4__ {TYPE_3__* t_data; int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  TM_Result ;
typedef  int /*<<< orphan*/  MultiXactStatus ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 scalar_t__ DoLockModesConflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleHeaderIndicatesMovedPartitions (TYPE_3__*) ; 
 int /*<<< orphan*/  ISUPDATE_from_mxstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCKMODE_from_mxstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TM_Deleted ; 
 int /*<<< orphan*/  TM_Ok ; 
 int /*<<< orphan*/  TM_SelfModified ; 
 int /*<<< orphan*/  TM_Updated ; 
 scalar_t__ TransactionIdDidAbort (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mxact_status_for_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static TM_Result
test_lockmode_for_conflict(MultiXactStatus status, TransactionId xid,
						   LockTupleMode mode, HeapTuple tup,
						   bool *needwait)
{
	MultiXactStatus wantedstatus;

	*needwait = false;
	wantedstatus = get_mxact_status_for_lock(mode, false);

	/*
	 * Note: we *must* check TransactionIdIsInProgress before
	 * TransactionIdDidAbort/Commit; see comment at top of heapam_visibility.c
	 * for an explanation.
	 */
	if (TransactionIdIsCurrentTransactionId(xid))
	{
		/*
		 * The tuple has already been locked by our own transaction.  This is
		 * very rare but can happen if multiple transactions are trying to
		 * lock an ancient version of the same tuple.
		 */
		return TM_SelfModified;
	}
	else if (TransactionIdIsInProgress(xid))
	{
		/*
		 * If the locking transaction is running, what we do depends on
		 * whether the lock modes conflict: if they do, then we must wait for
		 * it to finish; otherwise we can fall through to lock this tuple
		 * version without waiting.
		 */
		if (DoLockModesConflict(LOCKMODE_from_mxstatus(status),
								LOCKMODE_from_mxstatus(wantedstatus)))
		{
			*needwait = true;
		}

		/*
		 * If we set needwait above, then this value doesn't matter;
		 * otherwise, this value signals to caller that it's okay to proceed.
		 */
		return TM_Ok;
	}
	else if (TransactionIdDidAbort(xid))
		return TM_Ok;
	else if (TransactionIdDidCommit(xid))
	{
		/*
		 * The other transaction committed.  If it was only a locker, then the
		 * lock is completely gone now and we can return success; but if it
		 * was an update, then what we do depends on whether the two lock
		 * modes conflict.  If they conflict, then we must report error to
		 * caller. But if they don't, we can fall through to allow the current
		 * transaction to lock the tuple.
		 *
		 * Note: the reason we worry about ISUPDATE here is because as soon as
		 * a transaction ends, all its locks are gone and meaningless, and
		 * thus we can ignore them; whereas its updates persist.  In the
		 * TransactionIdIsInProgress case, above, we don't need to check
		 * because we know the lock is still "alive" and thus a conflict needs
		 * always be checked.
		 */
		if (!ISUPDATE_from_mxstatus(status))
			return TM_Ok;

		if (DoLockModesConflict(LOCKMODE_from_mxstatus(status),
								LOCKMODE_from_mxstatus(wantedstatus)))
		{
			/* bummer */
			if (!ItemPointerEquals(&tup->t_self, &tup->t_data->t_ctid) ||
				HeapTupleHeaderIndicatesMovedPartitions(tup->t_data))
				return TM_Updated;
			else
				return TM_Deleted;
		}

		return TM_Ok;
	}

	/* Not in progress, not aborted, not committed -- must have crashed */
	return TM_Ok;
}