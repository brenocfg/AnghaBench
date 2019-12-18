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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_2__ {int /*<<< orphan*/  recoveryWakeupLatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ArchiveRecoveryRequested ; 
 scalar_t__ CheckForStandbyTrigger () ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  HandleStartupProcInterrupts () ; 
 scalar_t__ RM_XACT_ID ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TimestampDifference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int*) ; 
 int /*<<< orphan*/  TimestampTzPlusMilliseconds (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WAIT_EVENT_RECOVERY_APPLY_DELAY ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ *,int,long,int /*<<< orphan*/ ) ; 
 int XLOG_XACT_COMMIT ; 
 int XLOG_XACT_COMMIT_PREPARED ; 
 int XLOG_XACT_OPMASK ; 
 TYPE_1__* XLogCtl ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetRmid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,long,int) ; 
 int /*<<< orphan*/  getRecordTimestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reachedConsistency ; 
 int /*<<< orphan*/  recoveryDelayUntilTime ; 
 scalar_t__ recovery_min_apply_delay ; 

__attribute__((used)) static bool
recoveryApplyDelay(XLogReaderState *record)
{
	uint8		xact_info;
	TimestampTz xtime;
	long		secs;
	int			microsecs;

	/* nothing to do if no delay configured */
	if (recovery_min_apply_delay <= 0)
		return false;

	/* no delay is applied on a database not yet consistent */
	if (!reachedConsistency)
		return false;

	/* nothing to do if crash recovery is requested */
	if (!ArchiveRecoveryRequested)
		return false;

	/*
	 * Is it a COMMIT record?
	 *
	 * We deliberately choose not to delay aborts since they have no effect on
	 * MVCC. We already allow replay of records that don't have a timestamp,
	 * so there is already opportunity for issues caused by early conflicts on
	 * standbys.
	 */
	if (XLogRecGetRmid(record) != RM_XACT_ID)
		return false;

	xact_info = XLogRecGetInfo(record) & XLOG_XACT_OPMASK;

	if (xact_info != XLOG_XACT_COMMIT &&
		xact_info != XLOG_XACT_COMMIT_PREPARED)
		return false;

	if (!getRecordTimestamp(record, &xtime))
		return false;

	recoveryDelayUntilTime =
		TimestampTzPlusMilliseconds(xtime, recovery_min_apply_delay);

	/*
	 * Exit without arming the latch if it's already past time to apply this
	 * record
	 */
	TimestampDifference(GetCurrentTimestamp(), recoveryDelayUntilTime,
						&secs, &microsecs);
	if (secs <= 0 && microsecs <= 0)
		return false;

	while (true)
	{
		ResetLatch(&XLogCtl->recoveryWakeupLatch);

		/* might change the trigger file's location */
		HandleStartupProcInterrupts();

		if (CheckForStandbyTrigger())
			break;

		/*
		 * Wait for difference between GetCurrentTimestamp() and
		 * recoveryDelayUntilTime
		 */
		TimestampDifference(GetCurrentTimestamp(), recoveryDelayUntilTime,
							&secs, &microsecs);

		/*
		 * NB: We're ignoring waits below recovery_min_apply_delay's
		 * resolution.
		 */
		if (secs <= 0 && microsecs / 1000 <= 0)
			break;

		elog(DEBUG2, "recovery apply delay %ld seconds, %d milliseconds",
			 secs, microsecs / 1000);

		(void) WaitLatch(&XLogCtl->recoveryWakeupLatch,
						 WL_LATCH_SET | WL_TIMEOUT | WL_EXIT_ON_PM_DEATH,
						 secs * 1000L + microsecs / 1000,
						 WAIT_EVENT_RECOVERY_APPLY_DELAY);
	}
	return true;
}