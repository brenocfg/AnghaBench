#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int TimeLineID ;

/* Variables and functions */
 int /*<<< orphan*/  ArchiveRecoveryRequested ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  EnableHotStandby ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PrimaryConnInfo ; 
 scalar_t__ RECOVERY_TARGET_ACTION_PAUSE ; 
 scalar_t__ RECOVERY_TARGET_ACTION_SHUTDOWN ; 
 scalar_t__ RECOVERY_TARGET_TIME ; 
 scalar_t__ RECOVERY_TARGET_TIMELINE_CONTROLFILE ; 
 scalar_t__ RECOVERY_TARGET_TIMELINE_LATEST ; 
 scalar_t__ RECOVERY_TARGET_TIMELINE_NUMERIC ; 
 scalar_t__ StandbyModeRequested ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  existsTimeLineHistory (int) ; 
 int findNewestTimeLine (int) ; 
 int /*<<< orphan*/ * recoveryRestoreCommand ; 
 scalar_t__ recoveryTarget ; 
 scalar_t__ recoveryTargetAction ; 
 int recoveryTargetTLI ; 
 int recoveryTargetTLIRequested ; 
 int /*<<< orphan*/  recoveryTargetTime ; 
 scalar_t__ recoveryTargetTimeLineGoal ; 
 int /*<<< orphan*/  recovery_target_time_string ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  timestamptz_in ; 

__attribute__((used)) static void
validateRecoveryParameters(void)
{
	if (!ArchiveRecoveryRequested)
		return;

	/*
	 * Check for compulsory parameters
	 */
	if (StandbyModeRequested)
	{
		if ((PrimaryConnInfo == NULL || strcmp(PrimaryConnInfo, "") == 0) &&
			(recoveryRestoreCommand == NULL || strcmp(recoveryRestoreCommand, "") == 0))
			ereport(WARNING,
					(errmsg("specified neither primary_conninfo nor restore_command"),
					 errhint("The database server will regularly poll the pg_wal subdirectory to check for files placed there.")));
	}
	else
	{
		if (recoveryRestoreCommand == NULL ||
			strcmp(recoveryRestoreCommand, "") == 0)
			ereport(FATAL,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("must specify restore_command when standby mode is not enabled")));
	}

	/*
	 * Override any inconsistent requests. Note that this is a change of
	 * behaviour in 9.5; prior to this we simply ignored a request to pause if
	 * hot_standby = off, which was surprising behaviour.
	 */
	if (recoveryTargetAction == RECOVERY_TARGET_ACTION_PAUSE &&
		!EnableHotStandby)
		recoveryTargetAction = RECOVERY_TARGET_ACTION_SHUTDOWN;

	/*
	 * Final parsing of recovery_target_time string; see also
	 * check_recovery_target_time().
	 */
	if (recoveryTarget == RECOVERY_TARGET_TIME)
	{
		recoveryTargetTime = DatumGetTimestampTz(DirectFunctionCall3(timestamptz_in,
																	 CStringGetDatum(recovery_target_time_string),
																	 ObjectIdGetDatum(InvalidOid),
																	 Int32GetDatum(-1)));
	}

	/*
	 * If user specified recovery_target_timeline, validate it or compute the
	 * "latest" value.  We can't do this until after we've gotten the restore
	 * command and set InArchiveRecovery, because we need to fetch timeline
	 * history files from the archive.
	 */
	if (recoveryTargetTimeLineGoal == RECOVERY_TARGET_TIMELINE_NUMERIC)
	{
		TimeLineID	rtli = recoveryTargetTLIRequested;

		/* Timeline 1 does not have a history file, all else should */
		if (rtli != 1 && !existsTimeLineHistory(rtli))
			ereport(FATAL,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("recovery target timeline %u does not exist",
							rtli)));
		recoveryTargetTLI = rtli;
	}
	else if (recoveryTargetTimeLineGoal == RECOVERY_TARGET_TIMELINE_LATEST)
	{
		/* We start the "latest" search from pg_control's timeline */
		recoveryTargetTLI = findNewestTimeLine(recoveryTargetTLI);
	}
	else
	{
		/*
		 * else we just use the recoveryTargetTLI as already read from
		 * ControlFile
		 */
		Assert(recoveryTargetTimeLineGoal == RECOVERY_TARGET_TIMELINE_CONTROLFILE);
	}
}