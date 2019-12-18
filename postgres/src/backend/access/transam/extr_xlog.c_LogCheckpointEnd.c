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
typedef  int uint64 ;
struct TYPE_4__ {long m_checkpoint_write_time; long m_checkpoint_sync_time; } ;
struct TYPE_3__ {int ckpt_longest_sync; int ckpt_sync_rels; int ckpt_agg_sync_time; int /*<<< orphan*/  ckpt_segs_recycled; int /*<<< orphan*/  ckpt_segs_removed; int /*<<< orphan*/  ckpt_segs_added; scalar_t__ ckpt_bufs_written; int /*<<< orphan*/  ckpt_end_t; int /*<<< orphan*/  ckpt_start_t; int /*<<< orphan*/  ckpt_sync_end_t; int /*<<< orphan*/  ckpt_sync_t; int /*<<< orphan*/  ckpt_write_t; } ;

/* Variables and functions */
 TYPE_2__ BgWriterStats ; 
 double CheckPointDistanceEstimate ; 
 TYPE_1__ CheckpointStats ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  LOG ; 
 double NBuffers ; 
 double PrevCheckPointDistance ; 
 int /*<<< orphan*/  TimestampDifference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,scalar_t__,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int,long,int,long,int,int,long,int,long,int,int,int) ; 
 int /*<<< orphan*/  log_checkpoints ; 

__attribute__((used)) static void
LogCheckpointEnd(bool restartpoint)
{
	long		write_secs,
				sync_secs,
				total_secs,
				longest_secs,
				average_secs;
	int			write_usecs,
				sync_usecs,
				total_usecs,
				longest_usecs,
				average_usecs;
	uint64		average_sync_time;

	CheckpointStats.ckpt_end_t = GetCurrentTimestamp();

	TimestampDifference(CheckpointStats.ckpt_write_t,
						CheckpointStats.ckpt_sync_t,
						&write_secs, &write_usecs);

	TimestampDifference(CheckpointStats.ckpt_sync_t,
						CheckpointStats.ckpt_sync_end_t,
						&sync_secs, &sync_usecs);

	/* Accumulate checkpoint timing summary data, in milliseconds. */
	BgWriterStats.m_checkpoint_write_time +=
		write_secs * 1000 + write_usecs / 1000;
	BgWriterStats.m_checkpoint_sync_time +=
		sync_secs * 1000 + sync_usecs / 1000;

	/*
	 * All of the published timing statistics are accounted for.  Only
	 * continue if a log message is to be written.
	 */
	if (!log_checkpoints)
		return;

	TimestampDifference(CheckpointStats.ckpt_start_t,
						CheckpointStats.ckpt_end_t,
						&total_secs, &total_usecs);

	/*
	 * Timing values returned from CheckpointStats are in microseconds.
	 * Convert to the second plus microsecond form that TimestampDifference
	 * returns for homogeneous printing.
	 */
	longest_secs = (long) (CheckpointStats.ckpt_longest_sync / 1000000);
	longest_usecs = CheckpointStats.ckpt_longest_sync -
		(uint64) longest_secs * 1000000;

	average_sync_time = 0;
	if (CheckpointStats.ckpt_sync_rels > 0)
		average_sync_time = CheckpointStats.ckpt_agg_sync_time /
			CheckpointStats.ckpt_sync_rels;
	average_secs = (long) (average_sync_time / 1000000);
	average_usecs = average_sync_time - (uint64) average_secs * 1000000;

	elog(LOG, "%s complete: wrote %d buffers (%.1f%%); "
		 "%d WAL file(s) added, %d removed, %d recycled; "
		 "write=%ld.%03d s, sync=%ld.%03d s, total=%ld.%03d s; "
		 "sync files=%d, longest=%ld.%03d s, average=%ld.%03d s; "
		 "distance=%d kB, estimate=%d kB",
		 restartpoint ? "restartpoint" : "checkpoint",
		 CheckpointStats.ckpt_bufs_written,
		 (double) CheckpointStats.ckpt_bufs_written * 100 / NBuffers,
		 CheckpointStats.ckpt_segs_added,
		 CheckpointStats.ckpt_segs_removed,
		 CheckpointStats.ckpt_segs_recycled,
		 write_secs, write_usecs / 1000,
		 sync_secs, sync_usecs / 1000,
		 total_secs, total_usecs / 1000,
		 CheckpointStats.ckpt_sync_rels,
		 longest_secs, longest_usecs / 1000,
		 average_secs, average_usecs / 1000,
		 (int) (PrevCheckPointDistance / 1024.0),
		 (int) (CheckPointDistanceEstimate / 1024.0));
}