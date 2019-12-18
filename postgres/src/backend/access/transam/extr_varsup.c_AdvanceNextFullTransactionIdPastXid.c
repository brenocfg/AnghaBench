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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ TransactionId ;
struct TYPE_2__ {int /*<<< orphan*/  nextFullXid; } ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 scalar_t__ AmStartupProcess () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FullTransactionIdFromEpochAndXid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* ShmemVariableCache ; 
 int /*<<< orphan*/  TransactionIdAdvance (scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdFollowsOrEquals (scalar_t__,scalar_t__) ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidGenLock ; 
 scalar_t__ unlikely (int) ; 

void
AdvanceNextFullTransactionIdPastXid(TransactionId xid)
{
	FullTransactionId newNextFullXid;
	TransactionId next_xid;
	uint32		epoch;

	/*
	 * It is safe to read nextFullXid without a lock, because this is only
	 * called from the startup process or single-process mode, meaning that no
	 * other process can modify it.
	 */
	Assert(AmStartupProcess() || !IsUnderPostmaster);

	/* Fast return if this isn't an xid high enough to move the needle. */
	next_xid = XidFromFullTransactionId(ShmemVariableCache->nextFullXid);
	if (!TransactionIdFollowsOrEquals(xid, next_xid))
		return;

	/*
	 * Compute the FullTransactionId that comes after the given xid.  To do
	 * this, we preserve the existing epoch, but detect when we've wrapped
	 * into a new epoch.  This is necessary because WAL records and 2PC state
	 * currently contain 32 bit xids.  The wrap logic is safe in those cases
	 * because the span of active xids cannot exceed one epoch at any given
	 * point in the WAL stream.
	 */
	TransactionIdAdvance(xid);
	epoch = EpochFromFullTransactionId(ShmemVariableCache->nextFullXid);
	if (unlikely(xid < next_xid))
		++epoch;
	newNextFullXid = FullTransactionIdFromEpochAndXid(epoch, xid);

	/*
	 * We still need to take a lock to modify the value when there are
	 * concurrent readers.
	 */
	LWLockAcquire(XidGenLock, LW_EXCLUSIVE);
	ShmemVariableCache->nextFullXid = newNextFullXid;
	LWLockRelease(XidGenLock);
}