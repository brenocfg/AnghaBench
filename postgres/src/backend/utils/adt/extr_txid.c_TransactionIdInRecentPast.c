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
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ TransactionId ;
struct TYPE_2__ {int /*<<< orphan*/  oldestClogXid; } ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLogTruncationLock ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadNextFullTransactionId () ; 
 TYPE_1__* ShmemVariableCache ; 
 int /*<<< orphan*/  TransactionIdIsNormal (scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdIsValid (scalar_t__) ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,int /*<<< orphan*/ ) ; 
 int U64FromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_FORMAT ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psprintf (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
TransactionIdInRecentPast(uint64 xid_with_epoch, TransactionId *extracted_xid)
{
	uint32		xid_epoch = (uint32) (xid_with_epoch >> 32);
	TransactionId xid = (TransactionId) xid_with_epoch;
	uint32		now_epoch;
	TransactionId now_epoch_next_xid;
	FullTransactionId now_fullxid;

	now_fullxid = ReadNextFullTransactionId();
	now_epoch_next_xid = XidFromFullTransactionId(now_fullxid);
	now_epoch = EpochFromFullTransactionId(now_fullxid);

	if (extracted_xid != NULL)
		*extracted_xid = xid;

	if (!TransactionIdIsValid(xid))
		return false;

	/* For non-normal transaction IDs, we can ignore the epoch. */
	if (!TransactionIdIsNormal(xid))
		return true;

	/* If the transaction ID is in the future, throw an error. */
	if (xid_with_epoch >= U64FromFullTransactionId(now_fullxid))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("transaction ID %s is in the future",
						psprintf(UINT64_FORMAT, xid_with_epoch))));

	/*
	 * ShmemVariableCache->oldestClogXid is protected by CLogTruncationLock,
	 * but we don't acquire that lock here.  Instead, we require the caller to
	 * acquire it, because the caller is presumably going to look up the
	 * returned XID.  If we took and released the lock within this function, a
	 * CLOG truncation could occur before the caller finished with the XID.
	 */
	Assert(LWLockHeldByMe(CLogTruncationLock));

	/*
	 * If the transaction ID has wrapped around, it's definitely too old to
	 * determine the commit status.  Otherwise, we can compare it to
	 * ShmemVariableCache->oldestClogXid to determine whether the relevant
	 * CLOG entry is guaranteed to still exist.
	 */
	if (xid_epoch + 1 < now_epoch
		|| (xid_epoch + 1 == now_epoch && xid < now_epoch_next_xid)
		|| TransactionIdPrecedes(xid, ShmemVariableCache->oldestClogXid))
		return false;

	return true;
}