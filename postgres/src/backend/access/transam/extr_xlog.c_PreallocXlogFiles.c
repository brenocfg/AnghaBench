#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_2__ {int /*<<< orphan*/  ckpt_segs_added; } ;

/* Variables and functions */
 TYPE_1__ CheckpointStats ; 
 int /*<<< orphan*/  XLByteToPrevSeg (scalar_t__,int /*<<< orphan*/ ,double) ; 
 int XLogFileInit (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ XLogSegmentOffset (scalar_t__,double) ; 
 int /*<<< orphan*/  close (int) ; 
 double wal_segment_size ; 

__attribute__((used)) static void
PreallocXlogFiles(XLogRecPtr endptr)
{
	XLogSegNo	_logSegNo;
	int			lf;
	bool		use_existent;
	uint64		offset;

	XLByteToPrevSeg(endptr, _logSegNo, wal_segment_size);
	offset = XLogSegmentOffset(endptr - 1, wal_segment_size);
	if (offset >= (uint32) (0.75 * wal_segment_size))
	{
		_logSegNo++;
		use_existent = true;
		lf = XLogFileInit(_logSegNo, &use_existent, true);
		close(lf);
		if (!use_existent)
			CheckpointStats.ckpt_segs_added++;
	}
}