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
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  SubTransGetParent (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANSACTION_STATUS_COMMITTED ; 
 scalar_t__ TRANSACTION_STATUS_SUB_COMMITTED ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionLogFetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionXmin ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

bool							/* true if given transaction committed */
TransactionIdDidCommit(TransactionId transactionId)
{
	XidStatus	xidstatus;

	xidstatus = TransactionLogFetch(transactionId);

	/*
	 * If it's marked committed, it's committed.
	 */
	if (xidstatus == TRANSACTION_STATUS_COMMITTED)
		return true;

	/*
	 * If it's marked subcommitted, we have to check the parent recursively.
	 * However, if it's older than TransactionXmin, we can't look at
	 * pg_subtrans; instead assume that the parent crashed without cleaning up
	 * its children.
	 *
	 * Originally we Assert'ed that the result of SubTransGetParent was not
	 * zero. However with the introduction of prepared transactions, there can
	 * be a window just after database startup where we do not have complete
	 * knowledge in pg_subtrans of the transactions after TransactionXmin.
	 * StartupSUBTRANS() has ensured that any missing information will be
	 * zeroed.  Since this case should not happen under normal conditions, it
	 * seems reasonable to emit a WARNING for it.
	 */
	if (xidstatus == TRANSACTION_STATUS_SUB_COMMITTED)
	{
		TransactionId parentXid;

		if (TransactionIdPrecedes(transactionId, TransactionXmin))
			return false;
		parentXid = SubTransGetParent(transactionId);
		if (!TransactionIdIsValid(parentXid))
		{
			elog(WARNING, "no pg_subtrans entry for subcommitted XID %u",
				 transactionId);
			return false;
		}
		return TransactionIdDidCommit(parentXid);
	}

	/*
	 * It's not committed.
	 */
	return false;
}