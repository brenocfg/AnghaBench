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
struct timeval {double tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ pg_time_t ;
typedef  scalar_t__ XLogRecPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 double CheckPointCompletionTarget ; 
 double CheckPointSegments ; 
 double CheckPointTimeout ; 
 scalar_t__ GetInsertRecPtr () ; 
 scalar_t__ GetXLogReplayRecPtr (int /*<<< orphan*/ *) ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  ckpt_active ; 
 double ckpt_cached_elapsed ; 
 scalar_t__ ckpt_start_recptr ; 
 scalar_t__ ckpt_start_time ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 double wal_segment_size ; 

__attribute__((used)) static bool
IsCheckpointOnSchedule(double progress)
{
	XLogRecPtr	recptr;
	struct timeval now;
	double		elapsed_xlogs,
				elapsed_time;

	Assert(ckpt_active);

	/* Scale progress according to checkpoint_completion_target. */
	progress *= CheckPointCompletionTarget;

	/*
	 * Check against the cached value first. Only do the more expensive
	 * calculations once we reach the target previously calculated. Since
	 * neither time or WAL insert pointer moves backwards, a freshly
	 * calculated value can only be greater than or equal to the cached value.
	 */
	if (progress < ckpt_cached_elapsed)
		return false;

	/*
	 * Check progress against WAL segments written and CheckPointSegments.
	 *
	 * We compare the current WAL insert location against the location
	 * computed before calling CreateCheckPoint. The code in XLogInsert that
	 * actually triggers a checkpoint when CheckPointSegments is exceeded
	 * compares against RedoRecPtr, so this is not completely accurate.
	 * However, it's good enough for our purposes, we're only calculating an
	 * estimate anyway.
	 *
	 * During recovery, we compare last replayed WAL record's location with
	 * the location computed before calling CreateRestartPoint. That maintains
	 * the same pacing as we have during checkpoints in normal operation, but
	 * we might exceed max_wal_size by a fair amount. That's because there can
	 * be a large gap between a checkpoint's redo-pointer and the checkpoint
	 * record itself, and we only start the restartpoint after we've seen the
	 * checkpoint record. (The gap is typically up to CheckPointSegments *
	 * checkpoint_completion_target where checkpoint_completion_target is the
	 * value that was in effect when the WAL was generated).
	 */
	if (RecoveryInProgress())
		recptr = GetXLogReplayRecPtr(NULL);
	else
		recptr = GetInsertRecPtr();
	elapsed_xlogs = (((double) (recptr - ckpt_start_recptr)) /
					 wal_segment_size) / CheckPointSegments;

	if (progress < elapsed_xlogs)
	{
		ckpt_cached_elapsed = elapsed_xlogs;
		return false;
	}

	/*
	 * Check progress against time elapsed and checkpoint_timeout.
	 */
	gettimeofday(&now, NULL);
	elapsed_time = ((double) ((pg_time_t) now.tv_sec - ckpt_start_time) +
					now.tv_usec / 1000000.0) / CheckPointTimeout;

	if (progress < elapsed_time)
	{
		ckpt_cached_elapsed = elapsed_time;
		return false;
	}

	/* It looks like we're on schedule. */
	return true;
}