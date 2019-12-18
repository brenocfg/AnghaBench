#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TransactionState ;
typedef  scalar_t__ TransactionId ;
struct TYPE_3__ {scalar_t__ state; int nChildXids; scalar_t__* childXids; int /*<<< orphan*/  fullTransactionId; struct TYPE_3__* parent; } ;

/* Variables and functions */
 TYPE_1__* CurrentTransactionState ; 
 int /*<<< orphan*/  FullTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ GetTopTransactionIdIfAny () ; 
 scalar_t__* ParallelCurrentXids ; 
 scalar_t__ TRANS_ABORT ; 
 scalar_t__ TransactionIdEquals (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdIsNormal (scalar_t__) ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,scalar_t__) ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int nParallelCurrentXids ; 

bool
TransactionIdIsCurrentTransactionId(TransactionId xid)
{
	TransactionState s;

	/*
	 * We always say that BootstrapTransactionId is "not my transaction ID"
	 * even when it is (ie, during bootstrap).  Along with the fact that
	 * transam.c always treats BootstrapTransactionId as already committed,
	 * this causes the heapam_visibility.c routines to see all tuples as
	 * committed, which is what we need during bootstrap.  (Bootstrap mode
	 * only inserts tuples, it never updates or deletes them, so all tuples
	 * can be presumed good immediately.)
	 *
	 * Likewise, InvalidTransactionId and FrozenTransactionId are certainly
	 * not my transaction ID, so we can just return "false" immediately for
	 * any non-normal XID.
	 */
	if (!TransactionIdIsNormal(xid))
		return false;

	if (TransactionIdEquals(xid, GetTopTransactionIdIfAny()))
		return true;

	/*
	 * In parallel workers, the XIDs we must consider as current are stored in
	 * ParallelCurrentXids rather than the transaction-state stack.  Note that
	 * the XIDs in this array are sorted numerically rather than according to
	 * transactionIdPrecedes order.
	 */
	if (nParallelCurrentXids > 0)
	{
		int			low,
					high;

		low = 0;
		high = nParallelCurrentXids - 1;
		while (low <= high)
		{
			int			middle;
			TransactionId probe;

			middle = low + (high - low) / 2;
			probe = ParallelCurrentXids[middle];
			if (probe == xid)
				return true;
			else if (probe < xid)
				low = middle + 1;
			else
				high = middle - 1;
		}
		return false;
	}

	/*
	 * We will return true for the Xid of the current subtransaction, any of
	 * its subcommitted children, any of its parents, or any of their
	 * previously subcommitted children.  However, a transaction being aborted
	 * is no longer "current", even though it may still have an entry on the
	 * state stack.
	 */
	for (s = CurrentTransactionState; s != NULL; s = s->parent)
	{
		int			low,
					high;

		if (s->state == TRANS_ABORT)
			continue;
		if (!FullTransactionIdIsValid(s->fullTransactionId))
			continue;			/* it can't have any child XIDs either */
		if (TransactionIdEquals(xid, XidFromFullTransactionId(s->fullTransactionId)))
			return true;
		/* As the childXids array is ordered, we can use binary search */
		low = 0;
		high = s->nChildXids - 1;
		while (low <= high)
		{
			int			middle;
			TransactionId probe;

			middle = low + (high - low) / 2;
			probe = s->childXids[middle];
			if (TransactionIdEquals(probe, xid))
				return true;
			else if (TransactionIdPrecedes(probe, xid))
				low = middle + 1;
			else
				high = middle - 1;
		}
	}

	return false;
}