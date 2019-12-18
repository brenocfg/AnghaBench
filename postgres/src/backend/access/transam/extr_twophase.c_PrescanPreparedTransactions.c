#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_6__ {int /*<<< orphan*/  nextFullXid; } ;
struct TYPE_5__ {int numPrepXacts; TYPE_1__** prepXacts; } ;
struct TYPE_4__ {int /*<<< orphan*/  ondisk; int /*<<< orphan*/  prepare_start_lsn; int /*<<< orphan*/  xid; int /*<<< orphan*/  inredo; } ;
typedef  TYPE_1__* GlobalTransaction ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 char* ProcessTwoPhaseBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ShmemVariableCache ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,int) ; 

TransactionId
PrescanPreparedTransactions(TransactionId **xids_p, int *nxids_p)
{
	FullTransactionId nextFullXid = ShmemVariableCache->nextFullXid;
	TransactionId origNextXid = XidFromFullTransactionId(nextFullXid);
	TransactionId result = origNextXid;
	TransactionId *xids = NULL;
	int			nxids = 0;
	int			allocsize = 0;
	int			i;

	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
	for (i = 0; i < TwoPhaseState->numPrepXacts; i++)
	{
		TransactionId xid;
		char	   *buf;
		GlobalTransaction gxact = TwoPhaseState->prepXacts[i];

		Assert(gxact->inredo);

		xid = gxact->xid;

		buf = ProcessTwoPhaseBuffer(xid,
									gxact->prepare_start_lsn,
									gxact->ondisk, false, true);

		if (buf == NULL)
			continue;

		/*
		 * OK, we think this file is valid.  Incorporate xid into the
		 * running-minimum result.
		 */
		if (TransactionIdPrecedes(xid, result))
			result = xid;

		if (xids_p)
		{
			if (nxids == allocsize)
			{
				if (nxids == 0)
				{
					allocsize = 10;
					xids = palloc(allocsize * sizeof(TransactionId));
				}
				else
				{
					allocsize = allocsize * 2;
					xids = repalloc(xids, allocsize * sizeof(TransactionId));
				}
			}
			xids[nxids++] = xid;
		}

		pfree(buf);
	}
	LWLockRelease(TwoPhaseStateLock);

	if (xids_p)
	{
		*xids_p = xids;
		*nxids_p = nxids;
	}

	return result;
}