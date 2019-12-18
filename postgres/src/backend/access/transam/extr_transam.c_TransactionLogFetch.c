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
typedef  scalar_t__ XidStatus ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  BootstrapTransactionId ; 
 int /*<<< orphan*/  FrozenTransactionId ; 
 scalar_t__ TRANSACTION_STATUS_ABORTED ; 
 scalar_t__ TRANSACTION_STATUS_COMMITTED ; 
 scalar_t__ TRANSACTION_STATUS_IN_PROGRESS ; 
 scalar_t__ TRANSACTION_STATUS_SUB_COMMITTED ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdGetStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cachedCommitLSN ; 
 int /*<<< orphan*/  cachedFetchXid ; 
 scalar_t__ cachedFetchXidStatus ; 

__attribute__((used)) static XidStatus
TransactionLogFetch(TransactionId transactionId)
{
	XidStatus	xidstatus;
	XLogRecPtr	xidlsn;

	/*
	 * Before going to the commit log manager, check our single item cache to
	 * see if we didn't just check the transaction status a moment ago.
	 */
	if (TransactionIdEquals(transactionId, cachedFetchXid))
		return cachedFetchXidStatus;

	/*
	 * Also, check to see if the transaction ID is a permanent one.
	 */
	if (!TransactionIdIsNormal(transactionId))
	{
		if (TransactionIdEquals(transactionId, BootstrapTransactionId))
			return TRANSACTION_STATUS_COMMITTED;
		if (TransactionIdEquals(transactionId, FrozenTransactionId))
			return TRANSACTION_STATUS_COMMITTED;
		return TRANSACTION_STATUS_ABORTED;
	}

	/*
	 * Get the transaction status.
	 */
	xidstatus = TransactionIdGetStatus(transactionId, &xidlsn);

	/*
	 * Cache it, but DO NOT cache status for unfinished or sub-committed
	 * transactions!  We only cache status that is guaranteed not to change.
	 */
	if (xidstatus != TRANSACTION_STATUS_IN_PROGRESS &&
		xidstatus != TRANSACTION_STATUS_SUB_COMMITTED)
	{
		cachedFetchXid = transactionId;
		cachedFetchXidStatus = xidstatus;
		cachedCommitLSN = xidlsn;
	}

	return xidstatus;
}