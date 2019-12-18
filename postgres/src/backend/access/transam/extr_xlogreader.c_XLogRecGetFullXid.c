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
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  scalar_t__ TransactionId ;
struct TYPE_2__ {int /*<<< orphan*/  nextFullXid; } ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 scalar_t__ AmStartupProcess () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FullTransactionIdFromEpochAndXid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 TYPE_1__* ShmemVariableCache ; 
 scalar_t__ XLogRecGetXid (int /*<<< orphan*/ *) ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

FullTransactionId
XLogRecGetFullXid(XLogReaderState *record)
{
	TransactionId	xid,
					next_xid;
	uint32			epoch;

	/*
	 * This function is only safe during replay, because it depends on the
	 * replay state.  See AdvanceNextFullTransactionIdPastXid() for more.
	 */
	Assert(AmStartupProcess() || !IsUnderPostmaster);

	xid = XLogRecGetXid(record);
	next_xid = XidFromFullTransactionId(ShmemVariableCache->nextFullXid);
	epoch = EpochFromFullTransactionId(ShmemVariableCache->nextFullXid);

	/*
	 * If xid is numerically greater than next_xid, it has to be from the
	 * last epoch.
	 */
	if (unlikely(xid > next_xid))
		--epoch;

	return FullTransactionIdFromEpochAndXid(epoch, xid);
}