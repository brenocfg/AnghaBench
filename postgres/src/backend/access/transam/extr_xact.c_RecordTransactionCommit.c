#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_2__ {int delayChkpt; } ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  RelFileNode ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufmgrCommit () ; 
 scalar_t__ DoNotReplicateId ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 scalar_t__ InvalidRepOriginId ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  LogStandbyInvalidations (int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* MyPgXact ; 
 int /*<<< orphan*/  MyXactFlags ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 scalar_t__ SYNCHRONOUS_COMMIT_OFF ; 
 int /*<<< orphan*/  SetCurrentTransactionStopTimestamp () ; 
 int /*<<< orphan*/  SyncRepWaitForLSN (scalar_t__,int) ; 
 int /*<<< orphan*/  TransactionIdAsyncCommitTree (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdCommitTree (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdLatest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionTreeSetCommitTsData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogFlush (scalar_t__) ; 
 int /*<<< orphan*/  XLogSetAsyncXactLSN (scalar_t__) ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 scalar_t__ XactLastCommitEnd ; 
 scalar_t__ XactLastRecEnd ; 
 int /*<<< orphan*/  XactLogCommitRecord (scalar_t__,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ forceSyncCommit ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replorigin_session_advance (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ replorigin_session_origin ; 
 int /*<<< orphan*/  replorigin_session_origin_lsn ; 
 scalar_t__ replorigin_session_origin_timestamp ; 
 int smgrGetPendingDeletes (int,int /*<<< orphan*/ **) ; 
 scalar_t__ synchronous_commit ; 
 int xactGetCommittedChildren (int /*<<< orphan*/ **) ; 
 int xactGetCommittedInvalidationMessages (int /*<<< orphan*/ **,int*) ; 
 scalar_t__ xactStopTimestamp ; 

__attribute__((used)) static TransactionId
RecordTransactionCommit(void)
{
	TransactionId xid = GetTopTransactionIdIfAny();
	bool		markXidCommitted = TransactionIdIsValid(xid);
	TransactionId latestXid = InvalidTransactionId;
	int			nrels;
	RelFileNode *rels;
	int			nchildren;
	TransactionId *children;
	int			nmsgs = 0;
	SharedInvalidationMessage *invalMessages = NULL;
	bool		RelcacheInitFileInval = false;
	bool		wrote_xlog;

	/* Get data needed for commit record */
	nrels = smgrGetPendingDeletes(true, &rels);
	nchildren = xactGetCommittedChildren(&children);
	if (XLogStandbyInfoActive())
		nmsgs = xactGetCommittedInvalidationMessages(&invalMessages,
													 &RelcacheInitFileInval);
	wrote_xlog = (XactLastRecEnd != 0);

	/*
	 * If we haven't been assigned an XID yet, we neither can, nor do we want
	 * to write a COMMIT record.
	 */
	if (!markXidCommitted)
	{
		/*
		 * We expect that every RelationDropStorage is followed by a catalog
		 * update, and hence XID assignment, so we shouldn't get here with any
		 * pending deletes.  Use a real test not just an Assert to check this,
		 * since it's a bit fragile.
		 */
		if (nrels != 0)
			elog(ERROR, "cannot commit a transaction that deleted files but has no xid");

		/* Can't have child XIDs either; AssignTransactionId enforces this */
		Assert(nchildren == 0);

		/*
		 * Transactions without an assigned xid can contain invalidation
		 * messages (e.g. explicit relcache invalidations or catcache
		 * invalidations for inplace updates); standbys need to process those.
		 * We can't emit a commit record without an xid, and we don't want to
		 * force assigning an xid, because that'd be problematic for e.g.
		 * vacuum.  Hence we emit a bespoke record for the invalidations. We
		 * don't want to use that in case a commit record is emitted, so they
		 * happen synchronously with commits (besides not wanting to emit more
		 * WAL records).
		 */
		if (nmsgs != 0)
		{
			LogStandbyInvalidations(nmsgs, invalMessages,
									RelcacheInitFileInval);
			wrote_xlog = true;	/* not strictly necessary */
		}

		/*
		 * If we didn't create XLOG entries, we're done here; otherwise we
		 * should trigger flushing those entries the same as a commit record
		 * would.  This will primarily happen for HOT pruning and the like; we
		 * want these to be flushed to disk in due time.
		 */
		if (!wrote_xlog)
			goto cleanup;
	}
	else
	{
		bool		replorigin;

		/*
		 * Are we using the replication origins feature?  Or, in other words,
		 * are we replaying remote actions?
		 */
		replorigin = (replorigin_session_origin != InvalidRepOriginId &&
					  replorigin_session_origin != DoNotReplicateId);

		/*
		 * Begin commit critical section and insert the commit XLOG record.
		 */
		/* Tell bufmgr and smgr to prepare for commit */
		BufmgrCommit();

		/*
		 * Mark ourselves as within our "commit critical section".  This
		 * forces any concurrent checkpoint to wait until we've updated
		 * pg_xact.  Without this, it is possible for the checkpoint to set
		 * REDO after the XLOG record but fail to flush the pg_xact update to
		 * disk, leading to loss of the transaction commit if the system
		 * crashes a little later.
		 *
		 * Note: we could, but don't bother to, set this flag in
		 * RecordTransactionAbort.  That's because loss of a transaction abort
		 * is noncritical; the presumption would be that it aborted, anyway.
		 *
		 * It's safe to change the delayChkpt flag of our own backend without
		 * holding the ProcArrayLock, since we're the only one modifying it.
		 * This makes checkpoint's determination of which xacts are delayChkpt
		 * a bit fuzzy, but it doesn't matter.
		 */
		START_CRIT_SECTION();
		MyPgXact->delayChkpt = true;

		SetCurrentTransactionStopTimestamp();

		XactLogCommitRecord(xactStopTimestamp,
							nchildren, children, nrels, rels,
							nmsgs, invalMessages,
							RelcacheInitFileInval, forceSyncCommit,
							MyXactFlags,
							InvalidTransactionId, NULL /* plain commit */ );

		if (replorigin)
			/* Move LSNs forward for this replication origin */
			replorigin_session_advance(replorigin_session_origin_lsn,
									   XactLastRecEnd);

		/*
		 * Record commit timestamp.  The value comes from plain commit
		 * timestamp if there's no replication origin; otherwise, the
		 * timestamp was already set in replorigin_session_origin_timestamp by
		 * replication.
		 *
		 * We don't need to WAL-log anything here, as the commit record
		 * written above already contains the data.
		 */

		if (!replorigin || replorigin_session_origin_timestamp == 0)
			replorigin_session_origin_timestamp = xactStopTimestamp;

		TransactionTreeSetCommitTsData(xid, nchildren, children,
									   replorigin_session_origin_timestamp,
									   replorigin_session_origin, false);
	}

	/*
	 * Check if we want to commit asynchronously.  We can allow the XLOG flush
	 * to happen asynchronously if synchronous_commit=off, or if the current
	 * transaction has not performed any WAL-logged operation or didn't assign
	 * an xid.  The transaction can end up not writing any WAL, even if it has
	 * an xid, if it only wrote to temporary and/or unlogged tables.  It can
	 * end up having written WAL without an xid if it did HOT pruning.  In
	 * case of a crash, the loss of such a transaction will be irrelevant;
	 * temp tables will be lost anyway, unlogged tables will be truncated and
	 * HOT pruning will be done again later. (Given the foregoing, you might
	 * think that it would be unnecessary to emit the XLOG record at all in
	 * this case, but we don't currently try to do that.  It would certainly
	 * cause problems at least in Hot Standby mode, where the
	 * KnownAssignedXids machinery requires tracking every XID assignment.  It
	 * might be OK to skip it only when wal_level < replica, but for now we
	 * don't.)
	 *
	 * However, if we're doing cleanup of any non-temp rels or committing any
	 * command that wanted to force sync commit, then we must flush XLOG
	 * immediately.  (We must not allow asynchronous commit if there are any
	 * non-temp tables to be deleted, because we might delete the files before
	 * the COMMIT record is flushed to disk.  We do allow asynchronous commit
	 * if all to-be-deleted tables are temporary though, since they are lost
	 * anyway if we crash.)
	 */
	if ((wrote_xlog && markXidCommitted &&
		 synchronous_commit > SYNCHRONOUS_COMMIT_OFF) ||
		forceSyncCommit || nrels > 0)
	{
		XLogFlush(XactLastRecEnd);

		/*
		 * Now we may update the CLOG, if we wrote a COMMIT record above
		 */
		if (markXidCommitted)
			TransactionIdCommitTree(xid, nchildren, children);
	}
	else
	{
		/*
		 * Asynchronous commit case:
		 *
		 * This enables possible committed transaction loss in the case of a
		 * postmaster crash because WAL buffers are left unwritten. Ideally we
		 * could issue the WAL write without the fsync, but some
		 * wal_sync_methods do not allow separate write/fsync.
		 *
		 * Report the latest async commit LSN, so that the WAL writer knows to
		 * flush this commit.
		 */
		XLogSetAsyncXactLSN(XactLastRecEnd);

		/*
		 * We must not immediately update the CLOG, since we didn't flush the
		 * XLOG. Instead, we store the LSN up to which the XLOG must be
		 * flushed before the CLOG may be updated.
		 */
		if (markXidCommitted)
			TransactionIdAsyncCommitTree(xid, nchildren, children, XactLastRecEnd);
	}

	/*
	 * If we entered a commit critical section, leave it now, and let
	 * checkpoints proceed.
	 */
	if (markXidCommitted)
	{
		MyPgXact->delayChkpt = false;
		END_CRIT_SECTION();
	}

	/* Compute latestXid while we have the child XIDs handy */
	latestXid = TransactionIdLatest(xid, nchildren, children);

	/*
	 * Wait for synchronous replication, if required. Similar to the decision
	 * above about using committing asynchronously we only want to wait if
	 * this backend assigned an xid and wrote WAL.  No need to wait if an xid
	 * was assigned due to temporary/unlogged tables or due to HOT pruning.
	 *
	 * Note that at this stage we have marked clog, but still show as running
	 * in the procarray and continue to hold locks.
	 */
	if (wrote_xlog && markXidCommitted)
		SyncRepWaitForLSN(XactLastRecEnd, true);

	/* remember end of last commit record */
	XactLastCommitEnd = XactLastRecEnd;

	/* Reset XactLastRecEnd until the next transaction writes something */
	XactLastRecEnd = 0;
cleanup:
	/* Clean up local data */
	if (rels)
		pfree(rels);

	return latestXid;
}