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
struct TYPE_4__ {int /*<<< orphan*/  PrevTimeLineID; void* ThisTimeLineID; int /*<<< orphan*/  end_time; } ;
typedef  TYPE_1__ xl_end_of_recovery ;
typedef  scalar_t__ pg_time_t ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_6__ {void* minRecoveryPointTLI; int /*<<< orphan*/  minRecoveryPoint; scalar_t__ time; } ;
struct TYPE_5__ {int /*<<< orphan*/  PrevTimeLineID; } ;

/* Variables and functions */
 TYPE_3__* ControlFile ; 
 int /*<<< orphan*/  ControlFileLock ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LocalSetXLogInsertAllowed () ; 
 int LocalXLogInsertAllowed ; 
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 void* ThisTimeLineID ; 
 int /*<<< orphan*/  UpdateControlFile () ; 
 int /*<<< orphan*/  WALInsertLockAcquireExclusive () ; 
 int /*<<< orphan*/  WALInsertLockRelease () ; 
 int /*<<< orphan*/  XLOG_END_OF_RECOVERY ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 TYPE_2__* XLogCtl ; 
 int /*<<< orphan*/  XLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CreateEndOfRecoveryRecord(void)
{
	xl_end_of_recovery xlrec;
	XLogRecPtr	recptr;

	/* sanity check */
	if (!RecoveryInProgress())
		elog(ERROR, "can only be used to end recovery");

	xlrec.end_time = GetCurrentTimestamp();

	WALInsertLockAcquireExclusive();
	xlrec.ThisTimeLineID = ThisTimeLineID;
	xlrec.PrevTimeLineID = XLogCtl->PrevTimeLineID;
	WALInsertLockRelease();

	LocalSetXLogInsertAllowed();

	START_CRIT_SECTION();

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, sizeof(xl_end_of_recovery));
	recptr = XLogInsert(RM_XLOG_ID, XLOG_END_OF_RECOVERY);

	XLogFlush(recptr);

	/*
	 * Update the control file so that crash recovery can follow the timeline
	 * changes to this point.
	 */
	LWLockAcquire(ControlFileLock, LW_EXCLUSIVE);
	ControlFile->time = (pg_time_t) time(NULL);
	ControlFile->minRecoveryPoint = recptr;
	ControlFile->minRecoveryPointTLI = ThisTimeLineID;
	UpdateControlFile();
	LWLockRelease(ControlFileLock);

	END_CRIT_SECTION();

	LocalXLogInsertAllowed = -1;	/* return to "check" state */
}