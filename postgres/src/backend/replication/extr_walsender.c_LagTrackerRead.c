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
struct TYPE_3__ {scalar_t__ lsn; scalar_t__ time; } ;
typedef  TYPE_1__ WalTimeSample ;
typedef  scalar_t__ TimestampTz ;
typedef  int TimeOffset ;
struct TYPE_4__ {size_t* read_heads; size_t write_head; TYPE_1__* buffer; TYPE_1__* last_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int LAG_TRACKER_BUFFER_SIZE ; 
 TYPE_2__* lag_tracker ; 

__attribute__((used)) static TimeOffset
LagTrackerRead(int head, XLogRecPtr lsn, TimestampTz now)
{
	TimestampTz time = 0;

	/* Read all unread samples up to this LSN or end of buffer. */
	while (lag_tracker->read_heads[head] != lag_tracker->write_head &&
		   lag_tracker->buffer[lag_tracker->read_heads[head]].lsn <= lsn)
	{
		time = lag_tracker->buffer[lag_tracker->read_heads[head]].time;
		lag_tracker->last_read[head] =
			lag_tracker->buffer[lag_tracker->read_heads[head]];
		lag_tracker->read_heads[head] =
			(lag_tracker->read_heads[head] + 1) % LAG_TRACKER_BUFFER_SIZE;
	}

	/*
	 * If the lag tracker is empty, that means the standby has processed
	 * everything we've ever sent so we should now clear 'last_read'.  If we
	 * didn't do that, we'd risk using a stale and irrelevant sample for
	 * interpolation at the beginning of the next burst of WAL after a period
	 * of idleness.
	 */
	if (lag_tracker->read_heads[head] == lag_tracker->write_head)
		lag_tracker->last_read[head].time = 0;

	if (time > now)
	{
		/* If the clock somehow went backwards, treat as not found. */
		return -1;
	}
	else if (time == 0)
	{
		/*
		 * We didn't cross a time.  If there is a future sample that we
		 * haven't reached yet, and we've already reached at least one sample,
		 * let's interpolate the local flushed time.  This is mainly useful
		 * for reporting a completely stuck apply position as having
		 * increasing lag, since otherwise we'd have to wait for it to
		 * eventually start moving again and cross one of our samples before
		 * we can show the lag increasing.
		 */
		if (lag_tracker->read_heads[head] == lag_tracker->write_head)
		{
			/* There are no future samples, so we can't interpolate. */
			return -1;
		}
		else if (lag_tracker->last_read[head].time != 0)
		{
			/* We can interpolate between last_read and the next sample. */
			double		fraction;
			WalTimeSample prev = lag_tracker->last_read[head];
			WalTimeSample next = lag_tracker->buffer[lag_tracker->read_heads[head]];

			if (lsn < prev.lsn)
			{
				/*
				 * Reported LSNs shouldn't normally go backwards, but it's
				 * possible when there is a timeline change.  Treat as not
				 * found.
				 */
				return -1;
			}

			Assert(prev.lsn < next.lsn);

			if (prev.time > next.time)
			{
				/* If the clock somehow went backwards, treat as not found. */
				return -1;
			}

			/* See how far we are between the previous and next samples. */
			fraction =
				(double) (lsn - prev.lsn) / (double) (next.lsn - prev.lsn);

			/* Scale the local flush time proportionally. */
			time = (TimestampTz)
				((double) prev.time + (next.time - prev.time) * fraction);
		}
		else
		{
			/*
			 * We have only a future sample, implying that we were entirely
			 * caught up but and now there is a new burst of WAL and the
			 * standby hasn't processed the first sample yet.  Until the
			 * standby reaches the future sample the best we can do is report
			 * the hypothetical lag if that sample were to be replayed now.
			 */
			time = lag_tracker->buffer[lag_tracker->read_heads[head]].time;
		}
	}

	/* Return the elapsed time since local flush time in microseconds. */
	Assert(time != 0);
	return now - time;
}