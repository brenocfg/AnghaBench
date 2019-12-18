#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  RelFileNode ;

/* Variables and functions */
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  GetCurrentTransactionIdIfAny () ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  MyXactFlags ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SetCurrentTransactionStopTimestamp () ; 
 int /*<<< orphan*/  TransactionIdAbortTree (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdLatest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogSetAsyncXactLSN (scalar_t__) ; 
 scalar_t__ XactLastRecEnd ; 
 int /*<<< orphan*/  XactLogAbortRecord (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XidCacheRemoveRunningXids (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int smgrGetPendingDeletes (int,int /*<<< orphan*/ **) ; 
 int xactGetCommittedChildren (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xactStopTimestamp ; 

__attribute__((used)) static TransactionId
RecordTransactionAbort(bool isSubXact)
{
	TransactionId xid = GetCurrentTransactionIdIfAny();
	TransactionId latestXid;
	int			nrels;
	RelFileNode *rels;
	int			nchildren;
	TransactionId *children;
	TimestampTz xact_time;

	/*
	 * If we haven't been assigned an XID, nobody will care whether we aborted
	 * or not.  Hence, we're done in that case.  It does not matter if we have
	 * rels to delete (note that this routine is not responsible for actually
	 * deleting 'em).  We cannot have any child XIDs, either.
	 */
	if (!TransactionIdIsValid(xid))
	{
		/* Reset XactLastRecEnd until the next transaction writes something */
		if (!isSubXact)
			XactLastRecEnd = 0;
		return InvalidTransactionId;
	}

	/*
	 * We have a valid XID, so we should write an ABORT record for it.
	 *
	 * We do not flush XLOG to disk here, since the default assumption after a
	 * crash would be that we aborted, anyway.  For the same reason, we don't
	 * need to worry about interlocking against checkpoint start.
	 */

	/*
	 * Check that we haven't aborted halfway through RecordTransactionCommit.
	 */
	if (TransactionIdDidCommit(xid))
		elog(PANIC, "cannot abort transaction %u, it was already committed",
			 xid);

	/* Fetch the data we need for the abort record */
	nrels = smgrGetPendingDeletes(false, &rels);
	nchildren = xactGetCommittedChildren(&children);

	/* XXX do we really need a critical section here? */
	START_CRIT_SECTION();

	/* Write the ABORT record */
	if (isSubXact)
		xact_time = GetCurrentTimestamp();
	else
	{
		SetCurrentTransactionStopTimestamp();
		xact_time = xactStopTimestamp;
	}

	XactLogAbortRecord(xact_time,
					   nchildren, children,
					   nrels, rels,
					   MyXactFlags, InvalidTransactionId,
					   NULL);

	/*
	 * Report the latest async abort LSN, so that the WAL writer knows to
	 * flush this abort. There's nothing to be gained by delaying this, since
	 * WALWriter may as well do this when it can. This is important with
	 * streaming replication because if we don't flush WAL regularly we will
	 * find that large aborts leave us with a long backlog for when commits
	 * occur after the abort, increasing our window of data loss should
	 * problems occur at that point.
	 */
	if (!isSubXact)
		XLogSetAsyncXactLSN(XactLastRecEnd);

	/*
	 * Mark the transaction aborted in clog.  This is not absolutely necessary
	 * but we may as well do it while we are here; also, in the subxact case
	 * it is helpful because XactLockTableWait makes use of it to avoid
	 * waiting for already-aborted subtransactions.  It is OK to do it without
	 * having flushed the ABORT record to disk, because in event of a crash
	 * we'd be assumed to have aborted anyway.
	 */
	TransactionIdAbortTree(xid, nchildren, children);

	END_CRIT_SECTION();

	/* Compute latestXid while we have the child XIDs handy */
	latestXid = TransactionIdLatest(xid, nchildren, children);

	/*
	 * If we're aborting a subtransaction, we can immediately remove failed
	 * XIDs from PGPROC's cache of running child XIDs.  We do that here for
	 * subxacts, because we already have the child XID array at hand.  For
	 * main xacts, the equivalent happens just after this function returns.
	 */
	if (isSubXact)
		XidCacheRemoveRunningXids(xid, nchildren, children, latestXid);

	/* Reset XactLastRecEnd until the next transaction writes something */
	if (!isSubXact)
		XactLastRecEnd = 0;

	/* And clean up local data */
	if (rels)
		pfree(rels);

	return latestXid;
}