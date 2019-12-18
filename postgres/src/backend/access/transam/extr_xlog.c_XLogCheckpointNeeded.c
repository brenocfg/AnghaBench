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
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ XLogSegNo ;

/* Variables and functions */
 int CheckPointSegments ; 
 int /*<<< orphan*/  RedoRecPtr ; 
 int /*<<< orphan*/  XLByteToSeg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static bool
XLogCheckpointNeeded(XLogSegNo new_segno)
{
	XLogSegNo	old_segno;

	XLByteToSeg(RedoRecPtr, old_segno, wal_segment_size);

	if (new_segno >= old_segno + (uint64) (CheckPointSegments - 1))
		return true;
	return false;
}