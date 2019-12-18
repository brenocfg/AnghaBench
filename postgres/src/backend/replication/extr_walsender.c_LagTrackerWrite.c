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
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_4__ {scalar_t__ last_lsn; int write_head; int* read_heads; TYPE_1__* buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  time; scalar_t__ lsn; } ;

/* Variables and functions */
 int LAG_TRACKER_BUFFER_SIZE ; 
 int NUM_SYNC_REP_WAIT_MODE ; 
 int /*<<< orphan*/  am_walsender ; 
 TYPE_2__* lag_tracker ; 

__attribute__((used)) static void
LagTrackerWrite(XLogRecPtr lsn, TimestampTz local_flush_time)
{
	bool		buffer_full;
	int			new_write_head;
	int			i;

	if (!am_walsender)
		return;

	/*
	 * If the lsn hasn't advanced since last time, then do nothing.  This way
	 * we only record a new sample when new WAL has been written.
	 */
	if (lag_tracker->last_lsn == lsn)
		return;
	lag_tracker->last_lsn = lsn;

	/*
	 * If advancing the write head of the circular buffer would crash into any
	 * of the read heads, then the buffer is full.  In other words, the
	 * slowest reader (presumably apply) is the one that controls the release
	 * of space.
	 */
	new_write_head = (lag_tracker->write_head + 1) % LAG_TRACKER_BUFFER_SIZE;
	buffer_full = false;
	for (i = 0; i < NUM_SYNC_REP_WAIT_MODE; ++i)
	{
		if (new_write_head == lag_tracker->read_heads[i])
			buffer_full = true;
	}

	/*
	 * If the buffer is full, for now we just rewind by one slot and overwrite
	 * the last sample, as a simple (if somewhat uneven) way to lower the
	 * sampling rate.  There may be better adaptive compaction algorithms.
	 */
	if (buffer_full)
	{
		new_write_head = lag_tracker->write_head;
		if (lag_tracker->write_head > 0)
			lag_tracker->write_head--;
		else
			lag_tracker->write_head = LAG_TRACKER_BUFFER_SIZE - 1;
	}

	/* Store a sample at the current write head position. */
	lag_tracker->buffer[lag_tracker->write_head].lsn = lsn;
	lag_tracker->buffer[lag_tracker->write_head].time = local_flush_time;
	lag_tracker->write_head = new_write_head;
}