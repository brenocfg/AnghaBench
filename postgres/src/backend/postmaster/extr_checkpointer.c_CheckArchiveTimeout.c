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
typedef  scalar_t__ pg_time_t ;
typedef  scalar_t__ XLogRecPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ GetLastImportantRecPtr () ; 
 scalar_t__ GetLastSegSwitchData (scalar_t__*) ; 
 scalar_t__ Max (scalar_t__,scalar_t__) ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ RequestXLogSwitch (int) ; 
 int XLogArchiveTimeout ; 
 scalar_t__ XLogSegmentOffset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ last_xlog_switch_time ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
CheckArchiveTimeout(void)
{
	pg_time_t	now;
	pg_time_t	last_time;
	XLogRecPtr	last_switch_lsn;

	if (XLogArchiveTimeout <= 0 || RecoveryInProgress())
		return;

	now = (pg_time_t) time(NULL);

	/* First we do a quick check using possibly-stale local state. */
	if ((int) (now - last_xlog_switch_time) < XLogArchiveTimeout)
		return;

	/*
	 * Update local state ... note that last_xlog_switch_time is the last time
	 * a switch was performed *or requested*.
	 */
	last_time = GetLastSegSwitchData(&last_switch_lsn);

	last_xlog_switch_time = Max(last_xlog_switch_time, last_time);

	/* Now we can do the real checks */
	if ((int) (now - last_xlog_switch_time) >= XLogArchiveTimeout)
	{
		/*
		 * Switch segment only when "important" WAL has been logged since the
		 * last segment switch (last_switch_lsn points to end of segment
		 * switch occurred in).
		 */
		if (GetLastImportantRecPtr() > last_switch_lsn)
		{
			XLogRecPtr	switchpoint;

			/* mark switch as unimportant, avoids triggering checkpoints */
			switchpoint = RequestXLogSwitch(true);

			/*
			 * If the returned pointer points exactly to a segment boundary,
			 * assume nothing happened.
			 */
			if (XLogSegmentOffset(switchpoint, wal_segment_size) != 0)
				elog(DEBUG1, "write-ahead log switch forced (archive_timeout=%d)",
					 XLogArchiveTimeout);
		}

		/*
		 * Update state in any case, so we don't retry constantly when the
		 * system is idle.
		 */
		last_xlog_switch_time = now;
	}
}