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
 double CheckPointCompletionTarget ; 
 int CheckPointSegments ; 
 scalar_t__ ConvertToXSegs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_wal_size_mb ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
CalculateCheckpointSegments(void)
{
	double		target;

	/*-------
	 * Calculate the distance at which to trigger a checkpoint, to avoid
	 * exceeding max_wal_size_mb. This is based on two assumptions:
	 *
	 * a) we keep WAL for only one checkpoint cycle (prior to PG11 we kept
	 *    WAL for two checkpoint cycles to allow us to recover from the
	 *    secondary checkpoint if the first checkpoint failed, though we
	 *    only did this on the master anyway, not on standby. Keeping just
	 *    one checkpoint simplifies processing and reduces disk space in
	 *    many smaller databases.)
	 * b) during checkpoint, we consume checkpoint_completion_target *
	 *	  number of segments consumed between checkpoints.
	 *-------
	 */
	target = (double) ConvertToXSegs(max_wal_size_mb, wal_segment_size) /
		(1.0 + CheckPointCompletionTarget);

	/* round down */
	CheckPointSegments = (int) target;

	if (CheckPointSegments < 1)
		CheckPointSegments = 1;
}