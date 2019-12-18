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
typedef  scalar_t__ XLogSegNo ;
typedef  double XLogRecPtr ;

/* Variables and functions */
 double CheckPointCompletionTarget ; 
 double CheckPointDistanceEstimate ; 
 scalar_t__ ConvertToXSegs (int /*<<< orphan*/ ,double) ; 
 scalar_t__ ceil (double) ; 
 int /*<<< orphan*/  max_wal_size_mb ; 
 int /*<<< orphan*/  min_wal_size_mb ; 
 double wal_segment_size ; 

__attribute__((used)) static XLogSegNo
XLOGfileslop(XLogRecPtr RedoRecPtr)
{
	XLogSegNo	minSegNo;
	XLogSegNo	maxSegNo;
	double		distance;
	XLogSegNo	recycleSegNo;

	/*
	 * Calculate the segment numbers that min_wal_size_mb and max_wal_size_mb
	 * correspond to. Always recycle enough segments to meet the minimum, and
	 * remove enough segments to stay below the maximum.
	 */
	minSegNo = RedoRecPtr / wal_segment_size +
		ConvertToXSegs(min_wal_size_mb, wal_segment_size) - 1;
	maxSegNo = RedoRecPtr / wal_segment_size +
		ConvertToXSegs(max_wal_size_mb, wal_segment_size) - 1;

	/*
	 * Between those limits, recycle enough segments to get us through to the
	 * estimated end of next checkpoint.
	 *
	 * To estimate where the next checkpoint will finish, assume that the
	 * system runs steadily consuming CheckPointDistanceEstimate bytes between
	 * every checkpoint.
	 */
	distance = (1.0 + CheckPointCompletionTarget) * CheckPointDistanceEstimate;
	/* add 10% for good measure. */
	distance *= 1.10;

	recycleSegNo = (XLogSegNo) ceil(((double) RedoRecPtr + distance) /
									wal_segment_size);

	if (recycleSegNo < minSegNo)
		recycleSegNo = minSegNo;
	if (recycleSegNo > maxSegNo)
		recycleSegNo = maxSegNo;

	return recycleSegNo;
}