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
typedef  void* pg_time_t ;
struct TYPE_4__ {int /*<<< orphan*/  redo; void* time; } ;
struct TYPE_5__ {int backupEndRequired; int wal_log_hints; int track_commit_timestamp; int MaxConnections; int max_wal_senders; int max_worker_processes; int max_locks_per_xact; scalar_t__ max_prepared_xacts; int /*<<< orphan*/  wal_level; scalar_t__ backupEndPoint; scalar_t__ backupStartPoint; scalar_t__ minRecoveryPointTLI; scalar_t__ minRecoveryPoint; TYPE_1__ checkPointCopy; int /*<<< orphan*/  checkPoint; void* time; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 TYPE_2__ ControlFile ; 
 int /*<<< orphan*/  DB_SHUTDOWNED ; 
 int /*<<< orphan*/  SizeOfXLogLongPHD ; 
 int /*<<< orphan*/  WAL_LEVEL_MINIMAL ; 
 int /*<<< orphan*/  WalSegSz ; 
 int /*<<< orphan*/  XLogSegNoOffsetToRecPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newXlogSegNo ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_controlfile (char*,TYPE_2__*,int) ; 

__attribute__((used)) static void
RewriteControlFile(void)
{
	/*
	 * Adjust fields as needed to force an empty XLOG starting at
	 * newXlogSegNo.
	 */
	XLogSegNoOffsetToRecPtr(newXlogSegNo, SizeOfXLogLongPHD, WalSegSz,
							ControlFile.checkPointCopy.redo);
	ControlFile.checkPointCopy.time = (pg_time_t) time(NULL);

	ControlFile.state = DB_SHUTDOWNED;
	ControlFile.time = (pg_time_t) time(NULL);
	ControlFile.checkPoint = ControlFile.checkPointCopy.redo;
	ControlFile.minRecoveryPoint = 0;
	ControlFile.minRecoveryPointTLI = 0;
	ControlFile.backupStartPoint = 0;
	ControlFile.backupEndPoint = 0;
	ControlFile.backupEndRequired = false;

	/*
	 * Force the defaults for max_* settings. The values don't really matter
	 * as long as wal_level='minimal'; the postmaster will reset these fields
	 * anyway at startup.
	 */
	ControlFile.wal_level = WAL_LEVEL_MINIMAL;
	ControlFile.wal_log_hints = false;
	ControlFile.track_commit_timestamp = false;
	ControlFile.MaxConnections = 100;
	ControlFile.max_wal_senders = 10;
	ControlFile.max_worker_processes = 8;
	ControlFile.max_prepared_xacts = 0;
	ControlFile.max_locks_per_xact = 64;

	/* The control file gets flushed here. */
	update_controlfile(".", &ControlFile, true);
}