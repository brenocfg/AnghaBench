#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int numPrepXacts; TYPE_1__** prepXacts; } ;
struct TYPE_3__ {int /*<<< orphan*/  ondisk; int /*<<< orphan*/  prepare_start_lsn; int /*<<< orphan*/  xid; int /*<<< orphan*/  inredo; } ;
typedef  TYPE_1__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 char* ProcessTwoPhaseBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  pfree (char*) ; 

void
StandbyRecoverPreparedTransactions(void)
{
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
									gxact->ondisk, false, false);
		if (buf != NULL)
			pfree(buf);
	}
	LWLockRelease(TwoPhaseStateLock);
}