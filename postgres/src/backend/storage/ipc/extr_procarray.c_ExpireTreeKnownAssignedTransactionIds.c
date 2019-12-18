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
struct TYPE_2__ {int /*<<< orphan*/  latestCompletedXid; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  KnownAssignedXidsRemoveTree (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 scalar_t__ STANDBY_INITIALIZED ; 
 TYPE_1__* ShmemVariableCache ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ standbyState ; 

void
ExpireTreeKnownAssignedTransactionIds(TransactionId xid, int nsubxids,
									  TransactionId *subxids, TransactionId max_xid)
{
	Assert(standbyState >= STANDBY_INITIALIZED);

	/*
	 * Uses same locking as transaction commit
	 */
	LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);

	KnownAssignedXidsRemoveTree(xid, nsubxids, subxids);

	/* As in ProcArrayEndTransaction, advance latestCompletedXid */
	if (TransactionIdPrecedes(ShmemVariableCache->latestCompletedXid,
							  max_xid))
		ShmemVariableCache->latestCompletedXid = max_xid;

	LWLockRelease(ProcArrayLock);
}