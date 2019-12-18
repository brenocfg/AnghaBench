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
typedef  int XLogSegNo ;
typedef  scalar_t__ XLogRecPtr ;

/* Variables and functions */
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  XLByteToSeg (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogGetReplicationSlotMinimumLSN () ; 
 scalar_t__ max_replication_slots ; 
 int wal_keep_segments ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
KeepLogSeg(XLogRecPtr recptr, XLogSegNo *logSegNo)
{
	XLogSegNo	segno;
	XLogRecPtr	keep;

	XLByteToSeg(recptr, segno, wal_segment_size);
	keep = XLogGetReplicationSlotMinimumLSN();

	/* compute limit for wal_keep_segments first */
	if (wal_keep_segments > 0)
	{
		/* avoid underflow, don't go below 1 */
		if (segno <= wal_keep_segments)
			segno = 1;
		else
			segno = segno - wal_keep_segments;
	}

	/* then check whether slots limit removal further */
	if (max_replication_slots > 0 && keep != InvalidXLogRecPtr)
	{
		XLogSegNo	slotSegNo;

		XLByteToSeg(keep, slotSegNo, wal_segment_size);

		if (slotSegNo <= 0)
			segno = 1;
		else if (slotSegNo < segno)
			segno = slotSegNo;
	}

	/* don't delete WAL segments newer than the calculated segment */
	if (segno < *logSegNo)
		*logSegNo = segno;
}