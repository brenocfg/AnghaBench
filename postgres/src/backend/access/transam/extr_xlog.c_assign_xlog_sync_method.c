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

/* Variables and functions */
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_SYNC_METHOD_ASSIGN ; 
 int /*<<< orphan*/  XLogFileClose () ; 
 int /*<<< orphan*/  XLogFileNameP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_sync_bit (int) ; 
 scalar_t__ openLogFile ; 
 int /*<<< orphan*/  openLogSegNo ; 
 scalar_t__ pg_fsync (scalar_t__) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int sync_method ; 

void
assign_xlog_sync_method(int new_sync_method, void *extra)
{
	if (sync_method != new_sync_method)
	{
		/*
		 * To ensure that no blocks escape unsynced, force an fsync on the
		 * currently open log segment (if any).  Also, if the open flag is
		 * changing, close the log file so it will be reopened (with new flag
		 * bit) at next use.
		 */
		if (openLogFile >= 0)
		{
			pgstat_report_wait_start(WAIT_EVENT_WAL_SYNC_METHOD_ASSIGN);
			if (pg_fsync(openLogFile) != 0)
				ereport(PANIC,
						(errcode_for_file_access(),
						 errmsg("could not fsync file \"%s\": %m",
								XLogFileNameP(ThisTimeLineID, openLogSegNo))));
			pgstat_report_wait_end();
			if (get_sync_bit(sync_method) != get_sync_bit(new_sync_method))
				XLogFileClose();
		}
	}
}