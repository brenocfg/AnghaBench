#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xlrec ;
struct TYPE_3__ {scalar_t__ track_commit_timestamp; scalar_t__ wal_log_hints; scalar_t__ wal_level; scalar_t__ max_locks_per_xact; scalar_t__ max_prepared_xacts; scalar_t__ max_wal_senders; scalar_t__ max_worker_processes; scalar_t__ MaxConnections; } ;
typedef  TYPE_1__ xl_parameter_change ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_4__ {scalar_t__ wal_level; scalar_t__ wal_log_hints; scalar_t__ MaxConnections; scalar_t__ max_worker_processes; scalar_t__ max_wal_senders; scalar_t__ max_prepared_xacts; scalar_t__ max_locks_per_xact; scalar_t__ track_commit_timestamp; } ;

/* Variables and functions */
 TYPE_2__* ControlFile ; 
 scalar_t__ MaxConnections ; 
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int /*<<< orphan*/  UpdateControlFile () ; 
 int /*<<< orphan*/  XLOG_PARAMETER_CHANGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogIsNeeded () ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 scalar_t__ max_locks_per_xact ; 
 scalar_t__ max_prepared_xacts ; 
 scalar_t__ max_wal_senders ; 
 scalar_t__ max_worker_processes ; 
 scalar_t__ track_commit_timestamp ; 
 scalar_t__ wal_level ; 
 scalar_t__ wal_log_hints ; 

__attribute__((used)) static void
XLogReportParameters(void)
{
	if (wal_level != ControlFile->wal_level ||
		wal_log_hints != ControlFile->wal_log_hints ||
		MaxConnections != ControlFile->MaxConnections ||
		max_worker_processes != ControlFile->max_worker_processes ||
		max_wal_senders != ControlFile->max_wal_senders ||
		max_prepared_xacts != ControlFile->max_prepared_xacts ||
		max_locks_per_xact != ControlFile->max_locks_per_xact ||
		track_commit_timestamp != ControlFile->track_commit_timestamp)
	{
		/*
		 * The change in number of backend slots doesn't need to be WAL-logged
		 * if archiving is not enabled, as you can't start archive recovery
		 * with wal_level=minimal anyway. We don't really care about the
		 * values in pg_control either if wal_level=minimal, but seems better
		 * to keep them up-to-date to avoid confusion.
		 */
		if (wal_level != ControlFile->wal_level || XLogIsNeeded())
		{
			xl_parameter_change xlrec;
			XLogRecPtr	recptr;

			xlrec.MaxConnections = MaxConnections;
			xlrec.max_worker_processes = max_worker_processes;
			xlrec.max_wal_senders = max_wal_senders;
			xlrec.max_prepared_xacts = max_prepared_xacts;
			xlrec.max_locks_per_xact = max_locks_per_xact;
			xlrec.wal_level = wal_level;
			xlrec.wal_log_hints = wal_log_hints;
			xlrec.track_commit_timestamp = track_commit_timestamp;

			XLogBeginInsert();
			XLogRegisterData((char *) &xlrec, sizeof(xlrec));

			recptr = XLogInsert(RM_XLOG_ID, XLOG_PARAMETER_CHANGE);
			XLogFlush(recptr);
		}

		ControlFile->MaxConnections = MaxConnections;
		ControlFile->max_worker_processes = max_worker_processes;
		ControlFile->max_wal_senders = max_wal_senders;
		ControlFile->max_prepared_xacts = max_prepared_xacts;
		ControlFile->max_locks_per_xact = max_locks_per_xact;
		ControlFile->wal_level = wal_level;
		ControlFile->wal_log_hints = wal_log_hints;
		ControlFile->track_commit_timestamp = track_commit_timestamp;
		UpdateControlFile();
	}
}