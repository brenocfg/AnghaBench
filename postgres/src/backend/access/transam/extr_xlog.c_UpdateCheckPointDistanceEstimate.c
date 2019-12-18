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
typedef  double uint64 ;

/* Variables and functions */
 double CheckPointDistanceEstimate ; 
 double PrevCheckPointDistance ; 

__attribute__((used)) static void
UpdateCheckPointDistanceEstimate(uint64 nbytes)
{
	/*
	 * To estimate the number of segments consumed between checkpoints, keep a
	 * moving average of the amount of WAL generated in previous checkpoint
	 * cycles. However, if the load is bursty, with quiet periods and busy
	 * periods, we want to cater for the peak load. So instead of a plain
	 * moving average, let the average decline slowly if the previous cycle
	 * used less WAL than estimated, but bump it up immediately if it used
	 * more.
	 *
	 * When checkpoints are triggered by max_wal_size, this should converge to
	 * CheckpointSegments * wal_segment_size,
	 *
	 * Note: This doesn't pay any attention to what caused the checkpoint.
	 * Checkpoints triggered manually with CHECKPOINT command, or by e.g.
	 * starting a base backup, are counted the same as those created
	 * automatically. The slow-decline will largely mask them out, if they are
	 * not frequent. If they are frequent, it seems reasonable to count them
	 * in as any others; if you issue a manual checkpoint every 5 minutes and
	 * never let a timed checkpoint happen, it makes sense to base the
	 * preallocation on that 5 minute interval rather than whatever
	 * checkpoint_timeout is set to.
	 */
	PrevCheckPointDistance = nbytes;
	if (CheckPointDistanceEstimate < nbytes)
		CheckPointDistanceEstimate = nbytes;
	else
		CheckPointDistanceEstimate =
			(0.90 * CheckPointDistanceEstimate + 0.10 * (double) nbytes);
}