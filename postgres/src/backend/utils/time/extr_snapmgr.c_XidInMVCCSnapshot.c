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
typedef  size_t uint32 ;
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_3__ {size_t subxcnt; size_t xcnt; int /*<<< orphan*/ * subxip; int /*<<< orphan*/  xmin; scalar_t__ suboverflowed; int /*<<< orphan*/ * xip; int /*<<< orphan*/  takenDuringRecovery; int /*<<< orphan*/  xmax; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  SubTransGetTopmostTransaction (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdFollowsOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
XidInMVCCSnapshot(TransactionId xid, Snapshot snapshot)
{
	uint32		i;

	/*
	 * Make a quick range check to eliminate most XIDs without looking at the
	 * xip arrays.  Note that this is OK even if we convert a subxact XID to
	 * its parent below, because a subxact with XID < xmin has surely also got
	 * a parent with XID < xmin, while one with XID >= xmax must belong to a
	 * parent that was not yet committed at the time of this snapshot.
	 */

	/* Any xid < xmin is not in-progress */
	if (TransactionIdPrecedes(xid, snapshot->xmin))
		return false;
	/* Any xid >= xmax is in-progress */
	if (TransactionIdFollowsOrEquals(xid, snapshot->xmax))
		return true;

	/*
	 * Snapshot information is stored slightly differently in snapshots taken
	 * during recovery.
	 */
	if (!snapshot->takenDuringRecovery)
	{
		/*
		 * If the snapshot contains full subxact data, the fastest way to
		 * check things is just to compare the given XID against both subxact
		 * XIDs and top-level XIDs.  If the snapshot overflowed, we have to
		 * use pg_subtrans to convert a subxact XID to its parent XID, but
		 * then we need only look at top-level XIDs not subxacts.
		 */
		if (!snapshot->suboverflowed)
		{
			/* we have full data, so search subxip */
			int32		j;

			for (j = 0; j < snapshot->subxcnt; j++)
			{
				if (TransactionIdEquals(xid, snapshot->subxip[j]))
					return true;
			}

			/* not there, fall through to search xip[] */
		}
		else
		{
			/*
			 * Snapshot overflowed, so convert xid to top-level.  This is safe
			 * because we eliminated too-old XIDs above.
			 */
			xid = SubTransGetTopmostTransaction(xid);

			/*
			 * If xid was indeed a subxact, we might now have an xid < xmin,
			 * so recheck to avoid an array scan.  No point in rechecking
			 * xmax.
			 */
			if (TransactionIdPrecedes(xid, snapshot->xmin))
				return false;
		}

		for (i = 0; i < snapshot->xcnt; i++)
		{
			if (TransactionIdEquals(xid, snapshot->xip[i]))
				return true;
		}
	}
	else
	{
		int32		j;

		/*
		 * In recovery we store all xids in the subxact array because it is by
		 * far the bigger array, and we mostly don't know which xids are
		 * top-level and which are subxacts. The xip array is empty.
		 *
		 * We start by searching subtrans, if we overflowed.
		 */
		if (snapshot->suboverflowed)
		{
			/*
			 * Snapshot overflowed, so convert xid to top-level.  This is safe
			 * because we eliminated too-old XIDs above.
			 */
			xid = SubTransGetTopmostTransaction(xid);

			/*
			 * If xid was indeed a subxact, we might now have an xid < xmin,
			 * so recheck to avoid an array scan.  No point in rechecking
			 * xmax.
			 */
			if (TransactionIdPrecedes(xid, snapshot->xmin))
				return false;
		}

		/*
		 * We now have either a top-level xid higher than xmin or an
		 * indeterminate xid. We don't know whether it's top level or subxact
		 * but it doesn't matter. If it's present, the xid is visible.
		 */
		for (j = 0; j < snapshot->subxcnt; j++)
		{
			if (TransactionIdEquals(xid, snapshot->subxip[j]))
				return true;
		}
	}

	return false;
}