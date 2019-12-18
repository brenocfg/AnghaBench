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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  RelFileNode ;

/* Variables and functions */
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int MyXactFlags ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SyncRepWaitForLSN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TransactionIdAbortTree (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 int XACT_FLAGS_ACQUIREDACCESSEXCLUSIVELOCK ; 
 int /*<<< orphan*/  XLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactLogAbortRecord (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RecordTransactionAbortPrepared(TransactionId xid,
							   int nchildren,
							   TransactionId *children,
							   int nrels,
							   RelFileNode *rels,
							   const char *gid)
{
	XLogRecPtr	recptr;

	/*
	 * Catch the scenario where we aborted partway through
	 * RecordTransactionCommitPrepared ...
	 */
	if (TransactionIdDidCommit(xid))
		elog(PANIC, "cannot abort transaction %u, it was already committed",
			 xid);

	START_CRIT_SECTION();

	/*
	 * Emit the XLOG commit record. Note that we mark 2PC aborts as
	 * potentially having AccessExclusiveLocks since we don't know whether or
	 * not they do.
	 */
	recptr = XactLogAbortRecord(GetCurrentTimestamp(),
								nchildren, children,
								nrels, rels,
								MyXactFlags | XACT_FLAGS_ACQUIREDACCESSEXCLUSIVELOCK,
								xid, gid);

	/* Always flush, since we're about to remove the 2PC state file */
	XLogFlush(recptr);

	/*
	 * Mark the transaction aborted in clog.  This is not absolutely necessary
	 * but we may as well do it while we are here.
	 */
	TransactionIdAbortTree(xid, nchildren, children);

	END_CRIT_SECTION();

	/*
	 * Wait for synchronous replication, if required.
	 *
	 * Note that at this stage we have marked clog, but still show as running
	 * in the procarray and continue to hold locks.
	 */
	SyncRepWaitForLSN(recptr, false);
}