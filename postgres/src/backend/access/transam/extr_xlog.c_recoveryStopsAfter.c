#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ twophase_xid; } ;
typedef  TYPE_1__ xl_xact_parsed_commit ;
struct TYPE_14__ {scalar_t__ twophase_xid; } ;
typedef  TYPE_2__ xl_xact_parsed_abort ;
typedef  int /*<<< orphan*/  xl_xact_commit ;
typedef  int /*<<< orphan*/  xl_xact_abort ;
struct TYPE_15__ {int /*<<< orphan*/  rp_name; } ;
typedef  TYPE_3__ xl_restore_point ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_16__ {scalar_t__ ReadRecPtr; } ;
typedef  TYPE_4__ XLogReaderState ;
typedef  scalar_t__ TransactionId ;
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  ArchiveRecoveryRequested ; 
 scalar_t__ InvalidTransactionId ; 
 int InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MAXFNAMELEN ; 
 int /*<<< orphan*/  ParseAbortRecord (scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ParseCommitRecord (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ RECOVERY_TARGET_IMMEDIATE ; 
 scalar_t__ RECOVERY_TARGET_LSN ; 
 scalar_t__ RECOVERY_TARGET_NAME ; 
 scalar_t__ RECOVERY_TARGET_XID ; 
 scalar_t__ RM_XACT_ID ; 
 scalar_t__ RM_XLOG_ID ; 
 int /*<<< orphan*/  SetLatestXTime (scalar_t__) ; 
 scalar_t__ XLOG_RESTORE_POINT ; 
 scalar_t__ XLOG_XACT_ABORT ; 
 scalar_t__ XLOG_XACT_ABORT_PREPARED ; 
 scalar_t__ XLOG_XACT_COMMIT ; 
 scalar_t__ XLOG_XACT_COMMIT_PREPARED ; 
 scalar_t__ XLOG_XACT_OPMASK ; 
 scalar_t__ XLR_INFO_MASK ; 
 scalar_t__ XLogRecGetData (TYPE_4__*) ; 
 scalar_t__ XLogRecGetInfo (TYPE_4__*) ; 
 scalar_t__ XLogRecGetRmid (TYPE_4__*) ; 
 scalar_t__ XLogRecGetXid (TYPE_4__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ getRecordTimestamp (TYPE_4__*,scalar_t__*) ; 
 scalar_t__ reachedConsistency ; 
 int recoveryStopAfter ; 
 int recoveryStopLSN ; 
 char* recoveryStopName ; 
 scalar_t__ recoveryStopTime ; 
 scalar_t__ recoveryStopXid ; 
 scalar_t__ recoveryTarget ; 
 scalar_t__ recoveryTargetInclusive ; 
 scalar_t__ recoveryTargetLSN ; 
 int /*<<< orphan*/  recoveryTargetName ; 
 scalar_t__ recoveryTargetXid ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_to_str (scalar_t__) ; 

__attribute__((used)) static bool
recoveryStopsAfter(XLogReaderState *record)
{
	uint8		info;
	uint8		xact_info;
	uint8		rmid;
	TimestampTz recordXtime;

	/*
	 * Ignore recovery target settings when not in archive recovery (meaning
	 * we are in crash recovery).
	 */
	if (!ArchiveRecoveryRequested)
		return false;

	info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;
	rmid = XLogRecGetRmid(record);

	/*
	 * There can be many restore points that share the same name; we stop at
	 * the first one.
	 */
	if (recoveryTarget == RECOVERY_TARGET_NAME &&
		rmid == RM_XLOG_ID && info == XLOG_RESTORE_POINT)
	{
		xl_restore_point *recordRestorePointData;

		recordRestorePointData = (xl_restore_point *) XLogRecGetData(record);

		if (strcmp(recordRestorePointData->rp_name, recoveryTargetName) == 0)
		{
			recoveryStopAfter = true;
			recoveryStopXid = InvalidTransactionId;
			recoveryStopLSN = InvalidXLogRecPtr;
			(void) getRecordTimestamp(record, &recoveryStopTime);
			strlcpy(recoveryStopName, recordRestorePointData->rp_name, MAXFNAMELEN);

			ereport(LOG,
					(errmsg("recovery stopping at restore point \"%s\", time %s",
							recoveryStopName,
							timestamptz_to_str(recoveryStopTime))));
			return true;
		}
	}

	/* Check if the target LSN has been reached */
	if (recoveryTarget == RECOVERY_TARGET_LSN &&
		recoveryTargetInclusive &&
		record->ReadRecPtr >= recoveryTargetLSN)
	{
		recoveryStopAfter = true;
		recoveryStopXid = InvalidTransactionId;
		recoveryStopLSN = record->ReadRecPtr;
		recoveryStopTime = 0;
		recoveryStopName[0] = '\0';
		ereport(LOG,
				(errmsg("recovery stopping after WAL location (LSN) \"%X/%X\"",
						(uint32) (recoveryStopLSN >> 32),
						(uint32) recoveryStopLSN)));
		return true;
	}

	if (rmid != RM_XACT_ID)
		return false;

	xact_info = info & XLOG_XACT_OPMASK;

	if (xact_info == XLOG_XACT_COMMIT ||
		xact_info == XLOG_XACT_COMMIT_PREPARED ||
		xact_info == XLOG_XACT_ABORT ||
		xact_info == XLOG_XACT_ABORT_PREPARED)
	{
		TransactionId recordXid;

		/* Update the last applied transaction timestamp */
		if (getRecordTimestamp(record, &recordXtime))
			SetLatestXTime(recordXtime);

		/* Extract the XID of the committed/aborted transaction */
		if (xact_info == XLOG_XACT_COMMIT_PREPARED)
		{
			xl_xact_commit *xlrec = (xl_xact_commit *) XLogRecGetData(record);
			xl_xact_parsed_commit parsed;

			ParseCommitRecord(XLogRecGetInfo(record),
							  xlrec,
							  &parsed);
			recordXid = parsed.twophase_xid;
		}
		else if (xact_info == XLOG_XACT_ABORT_PREPARED)
		{
			xl_xact_abort *xlrec = (xl_xact_abort *) XLogRecGetData(record);
			xl_xact_parsed_abort parsed;

			ParseAbortRecord(XLogRecGetInfo(record),
							 xlrec,
							 &parsed);
			recordXid = parsed.twophase_xid;
		}
		else
			recordXid = XLogRecGetXid(record);

		/*
		 * There can be only one transaction end record with this exact
		 * transactionid
		 *
		 * when testing for an xid, we MUST test for equality only, since
		 * transactions are numbered in the order they start, not the order
		 * they complete. A higher numbered xid will complete before you about
		 * 50% of the time...
		 */
		if (recoveryTarget == RECOVERY_TARGET_XID && recoveryTargetInclusive &&
			recordXid == recoveryTargetXid)
		{
			recoveryStopAfter = true;
			recoveryStopXid = recordXid;
			recoveryStopTime = recordXtime;
			recoveryStopLSN = InvalidXLogRecPtr;
			recoveryStopName[0] = '\0';

			if (xact_info == XLOG_XACT_COMMIT ||
				xact_info == XLOG_XACT_COMMIT_PREPARED)
			{
				ereport(LOG,
						(errmsg("recovery stopping after commit of transaction %u, time %s",
								recoveryStopXid,
								timestamptz_to_str(recoveryStopTime))));
			}
			else if (xact_info == XLOG_XACT_ABORT ||
					 xact_info == XLOG_XACT_ABORT_PREPARED)
			{
				ereport(LOG,
						(errmsg("recovery stopping after abort of transaction %u, time %s",
								recoveryStopXid,
								timestamptz_to_str(recoveryStopTime))));
			}
			return true;
		}
	}

	/* Check if we should stop as soon as reaching consistency */
	if (recoveryTarget == RECOVERY_TARGET_IMMEDIATE && reachedConsistency)
	{
		ereport(LOG,
				(errmsg("recovery stopping after reaching consistency")));

		recoveryStopAfter = true;
		recoveryStopXid = InvalidTransactionId;
		recoveryStopTime = 0;
		recoveryStopLSN = InvalidXLogRecPtr;
		recoveryStopName[0] = '\0';
		return true;
	}

	return false;
}