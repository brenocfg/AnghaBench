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
struct TYPE_2__ {int tailKnownAssignedXids; int headKnownAssignedXids; int /*<<< orphan*/  known_assigned_xids_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/ * KnownAssignedXids ; 
 scalar_t__* KnownAssignedXidsValid ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ TransactionIdFollowsOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* procArray ; 

__attribute__((used)) static int
KnownAssignedXidsGetAndSetXmin(TransactionId *xarray, TransactionId *xmin,
							   TransactionId xmax)
{
	int			count = 0;
	int			head,
				tail;
	int			i;

	/*
	 * Fetch head just once, since it may change while we loop. We can stop
	 * once we reach the initially seen head, since we are certain that an xid
	 * cannot enter and then leave the array while we hold ProcArrayLock.  We
	 * might miss newly-added xids, but they should be >= xmax so irrelevant
	 * anyway.
	 *
	 * Must take spinlock to ensure we see up-to-date array contents.
	 */
	SpinLockAcquire(&procArray->known_assigned_xids_lck);
	tail = procArray->tailKnownAssignedXids;
	head = procArray->headKnownAssignedXids;
	SpinLockRelease(&procArray->known_assigned_xids_lck);

	for (i = tail; i < head; i++)
	{
		/* Skip any gaps in the array */
		if (KnownAssignedXidsValid[i])
		{
			TransactionId knownXid = KnownAssignedXids[i];

			/*
			 * Update xmin if required.  Only the first XID need be checked,
			 * since the array is sorted.
			 */
			if (count == 0 &&
				TransactionIdPrecedes(knownXid, *xmin))
				*xmin = knownXid;

			/*
			 * Filter out anything >= xmax, again relying on sorted property
			 * of array.
			 */
			if (TransactionIdIsValid(xmax) &&
				TransactionIdFollowsOrEquals(knownXid, xmax))
				break;

			/* Add knownXid into output array */
			xarray[count++] = knownXid;
		}
	}

	return count;
}