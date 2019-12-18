#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  twophase_xid; } ;
typedef  TYPE_1__ xl_xact_parsed_commit ;
struct TYPE_16__ {int /*<<< orphan*/  twophase_xid; } ;
typedef  TYPE_2__ xl_xact_parsed_abort ;
typedef  int /*<<< orphan*/  xl_xact_commit ;
struct TYPE_17__ {int /*<<< orphan*/  xsub; int /*<<< orphan*/  nsubxacts; int /*<<< orphan*/  xtop; } ;
typedef  TYPE_3__ xl_xact_assignment ;
typedef  int /*<<< orphan*/  xl_xact_abort ;
typedef  scalar_t__ uint8 ;
struct TYPE_18__ {int /*<<< orphan*/  EndRecPtr; int /*<<< orphan*/  ReadRecPtr; } ;
typedef  TYPE_4__ XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  ParseAbortRecord (scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ParseCommitRecord (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PrepareRedoAdd (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrepareRedoRemove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ProcArrayApplyXidAssignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STANDBY_INITIALIZED ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 scalar_t__ XLOG_XACT_ABORT ; 
 scalar_t__ XLOG_XACT_ABORT_PREPARED ; 
 scalar_t__ XLOG_XACT_ASSIGNMENT ; 
 scalar_t__ XLOG_XACT_COMMIT ; 
 scalar_t__ XLOG_XACT_COMMIT_PREPARED ; 
 scalar_t__ XLOG_XACT_OPMASK ; 
 scalar_t__ XLOG_XACT_PREPARE ; 
 scalar_t__ XLogRecGetData (TYPE_4__*) ; 
 scalar_t__ XLogRecGetInfo (TYPE_4__*) ; 
 int /*<<< orphan*/  XLogRecGetOrigin (TYPE_4__*) ; 
 int /*<<< orphan*/  XLogRecGetXid (TYPE_4__*) ; 
 int /*<<< orphan*/  XLogRecHasAnyBlockRefs (TYPE_4__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ standbyState ; 
 int /*<<< orphan*/  xact_redo_abort (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xact_redo_commit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xact_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & XLOG_XACT_OPMASK;

	/* Backup blocks are not used in xact records */
	Assert(!XLogRecHasAnyBlockRefs(record));

	if (info == XLOG_XACT_COMMIT)
	{
		xl_xact_commit *xlrec = (xl_xact_commit *) XLogRecGetData(record);
		xl_xact_parsed_commit parsed;

		ParseCommitRecord(XLogRecGetInfo(record), xlrec, &parsed);
		xact_redo_commit(&parsed, XLogRecGetXid(record),
						 record->EndRecPtr, XLogRecGetOrigin(record));
	}
	else if (info == XLOG_XACT_COMMIT_PREPARED)
	{
		xl_xact_commit *xlrec = (xl_xact_commit *) XLogRecGetData(record);
		xl_xact_parsed_commit parsed;

		ParseCommitRecord(XLogRecGetInfo(record), xlrec, &parsed);
		xact_redo_commit(&parsed, parsed.twophase_xid,
						 record->EndRecPtr, XLogRecGetOrigin(record));

		/* Delete TwoPhaseState gxact entry and/or 2PC file. */
		LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
		PrepareRedoRemove(parsed.twophase_xid, false);
		LWLockRelease(TwoPhaseStateLock);
	}
	else if (info == XLOG_XACT_ABORT)
	{
		xl_xact_abort *xlrec = (xl_xact_abort *) XLogRecGetData(record);
		xl_xact_parsed_abort parsed;

		ParseAbortRecord(XLogRecGetInfo(record), xlrec, &parsed);
		xact_redo_abort(&parsed, XLogRecGetXid(record));
	}
	else if (info == XLOG_XACT_ABORT_PREPARED)
	{
		xl_xact_abort *xlrec = (xl_xact_abort *) XLogRecGetData(record);
		xl_xact_parsed_abort parsed;

		ParseAbortRecord(XLogRecGetInfo(record), xlrec, &parsed);
		xact_redo_abort(&parsed, parsed.twophase_xid);

		/* Delete TwoPhaseState gxact entry and/or 2PC file. */
		LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
		PrepareRedoRemove(parsed.twophase_xid, false);
		LWLockRelease(TwoPhaseStateLock);
	}
	else if (info == XLOG_XACT_PREPARE)
	{
		/*
		 * Store xid and start/end pointers of the WAL record in TwoPhaseState
		 * gxact entry.
		 */
		LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
		PrepareRedoAdd(XLogRecGetData(record),
					   record->ReadRecPtr,
					   record->EndRecPtr,
					   XLogRecGetOrigin(record));
		LWLockRelease(TwoPhaseStateLock);
	}
	else if (info == XLOG_XACT_ASSIGNMENT)
	{
		xl_xact_assignment *xlrec = (xl_xact_assignment *) XLogRecGetData(record);

		if (standbyState >= STANDBY_INITIALIZED)
			ProcArrayApplyXidAssignment(xlrec->xtop,
										xlrec->nsubxacts, xlrec->xsub);
	}
	else
		elog(PANIC, "xact_redo: unknown op code %u", info);
}