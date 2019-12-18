#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int nxids; int /*<<< orphan*/  overflowed; } ;
struct TYPE_5__ {int /*<<< orphan*/ * xids; } ;
struct TYPE_7__ {TYPE_1__ subxids; } ;
struct TYPE_6__ {int /*<<< orphan*/  latestCompletedXid; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_4__* MyPgXact ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 TYPE_2__* ShmemVariableCache ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XidCacheRemove (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
XidCacheRemoveRunningXids(TransactionId xid,
						  int nxids, const TransactionId *xids,
						  TransactionId latestXid)
{
	int			i,
				j;

	Assert(TransactionIdIsValid(xid));

	/*
	 * We must hold ProcArrayLock exclusively in order to remove transactions
	 * from the PGPROC array.  (See src/backend/access/transam/README.)  It's
	 * possible this could be relaxed since we know this routine is only used
	 * to abort subtransactions, but pending closer analysis we'd best be
	 * conservative.
	 *
	 * Note that we do not have to be careful about memory ordering of our own
	 * reads wrt. GetNewTransactionId() here - only this process can modify
	 * relevant fields of MyProc/MyPgXact.  But we do have to be careful about
	 * our own writes being well ordered.
	 */
	LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);

	/*
	 * Under normal circumstances xid and xids[] will be in increasing order,
	 * as will be the entries in subxids.  Scan backwards to avoid O(N^2)
	 * behavior when removing a lot of xids.
	 */
	for (i = nxids - 1; i >= 0; i--)
	{
		TransactionId anxid = xids[i];

		for (j = MyPgXact->nxids - 1; j >= 0; j--)
		{
			if (TransactionIdEquals(MyProc->subxids.xids[j], anxid))
			{
				XidCacheRemove(j);
				break;
			}
		}

		/*
		 * Ordinarily we should have found it, unless the cache has
		 * overflowed. However it's also possible for this routine to be
		 * invoked multiple times for the same subtransaction, in case of an
		 * error during AbortSubTransaction.  So instead of Assert, emit a
		 * debug warning.
		 */
		if (j < 0 && !MyPgXact->overflowed)
			elog(WARNING, "did not find subXID %u in MyProc", anxid);
	}

	for (j = MyPgXact->nxids - 1; j >= 0; j--)
	{
		if (TransactionIdEquals(MyProc->subxids.xids[j], xid))
		{
			XidCacheRemove(j);
			break;
		}
	}
	/* Ordinarily we should have found it, unless the cache has overflowed */
	if (j < 0 && !MyPgXact->overflowed)
		elog(WARNING, "did not find subXID %u in MyProc", xid);

	/* Also advance global latestCompletedXid while holding the lock */
	if (TransactionIdPrecedes(ShmemVariableCache->latestCompletedXid,
							  latestXid))
		ShmemVariableCache->latestCompletedXid = latestXid;

	LWLockRelease(ProcArrayLock);
}