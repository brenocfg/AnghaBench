#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int xcnt; int subxcnt; int /*<<< orphan*/  latestCompletedXid; int /*<<< orphan*/  oldestRunningXid; int /*<<< orphan*/  nextXid; scalar_t__ subxid_overflow; } ;
typedef  TYPE_1__ xl_running_xacts ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {int xcnt; int subxcnt; int /*<<< orphan*/  nextXid; int /*<<< orphan*/  latestCompletedXid; int /*<<< orphan*/  oldestRunningXid; scalar_t__ subxid_overflow; scalar_t__ xids; } ;
typedef  TYPE_2__* RunningTransactions ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int MinSizeOfXactRunningXacts ; 
 int /*<<< orphan*/  RM_STANDBY_ID ; 
 int /*<<< orphan*/  XLOG_MARK_UNIMPORTANT ; 
 int /*<<< orphan*/  XLOG_RUNNING_XACTS ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  XLogSetAsyncXactLSN (int) ; 
 int /*<<< orphan*/  XLogSetRecordFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

__attribute__((used)) static XLogRecPtr
LogCurrentRunningXacts(RunningTransactions CurrRunningXacts)
{
	xl_running_xacts xlrec;
	XLogRecPtr	recptr;

	xlrec.xcnt = CurrRunningXacts->xcnt;
	xlrec.subxcnt = CurrRunningXacts->subxcnt;
	xlrec.subxid_overflow = CurrRunningXacts->subxid_overflow;
	xlrec.nextXid = CurrRunningXacts->nextXid;
	xlrec.oldestRunningXid = CurrRunningXacts->oldestRunningXid;
	xlrec.latestCompletedXid = CurrRunningXacts->latestCompletedXid;

	/* Header */
	XLogBeginInsert();
	XLogSetRecordFlags(XLOG_MARK_UNIMPORTANT);
	XLogRegisterData((char *) (&xlrec), MinSizeOfXactRunningXacts);

	/* array of TransactionIds */
	if (xlrec.xcnt > 0)
		XLogRegisterData((char *) CurrRunningXacts->xids,
						 (xlrec.xcnt + xlrec.subxcnt) * sizeof(TransactionId));

	recptr = XLogInsert(RM_STANDBY_ID, XLOG_RUNNING_XACTS);

	if (CurrRunningXacts->subxid_overflow)
		elog(trace_recovery(DEBUG2),
			 "snapshot of %u running transactions overflowed (lsn %X/%X oldest xid %u latest complete %u next xid %u)",
			 CurrRunningXacts->xcnt,
			 (uint32) (recptr >> 32), (uint32) recptr,
			 CurrRunningXacts->oldestRunningXid,
			 CurrRunningXacts->latestCompletedXid,
			 CurrRunningXacts->nextXid);
	else
		elog(trace_recovery(DEBUG2),
			 "snapshot of %u+%u running transaction ids (lsn %X/%X oldest xid %u latest complete %u next xid %u)",
			 CurrRunningXacts->xcnt, CurrRunningXacts->subxcnt,
			 (uint32) (recptr >> 32), (uint32) recptr,
			 CurrRunningXacts->oldestRunningXid,
			 CurrRunningXacts->latestCompletedXid,
			 CurrRunningXacts->nextXid);

	/*
	 * Ensure running_xacts information is synced to disk not too far in the
	 * future. We don't want to stall anything though (i.e. use XLogFlush()),
	 * so we let the wal writer do it during normal operation.
	 * XLogSetAsyncXactLSN() conveniently will mark the LSN as to-be-synced
	 * and nudge the WALWriter into action if sleeping. Check
	 * XLogBackgroundFlush() for details why a record might not be flushed
	 * without it.
	 */
	XLogSetAsyncXactLSN(recptr);

	return recptr;
}