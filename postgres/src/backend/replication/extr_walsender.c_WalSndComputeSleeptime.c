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
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  TimestampDifference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int*) ; 
 int /*<<< orphan*/  TimestampTzPlusMilliseconds (scalar_t__,int) ; 
 scalar_t__ last_reply_timestamp ; 
 int /*<<< orphan*/  waiting_for_ping_response ; 
 int wal_sender_timeout ; 

__attribute__((used)) static long
WalSndComputeSleeptime(TimestampTz now)
{
	long		sleeptime = 10000;	/* 10 s */

	if (wal_sender_timeout > 0 && last_reply_timestamp > 0)
	{
		TimestampTz wakeup_time;
		long		sec_to_timeout;
		int			microsec_to_timeout;

		/*
		 * At the latest stop sleeping once wal_sender_timeout has been
		 * reached.
		 */
		wakeup_time = TimestampTzPlusMilliseconds(last_reply_timestamp,
												  wal_sender_timeout);

		/*
		 * If no ping has been sent yet, wakeup when it's time to do so.
		 * WalSndKeepaliveIfNecessary() wants to send a keepalive once half of
		 * the timeout passed without a response.
		 */
		if (!waiting_for_ping_response)
			wakeup_time = TimestampTzPlusMilliseconds(last_reply_timestamp,
													  wal_sender_timeout / 2);

		/* Compute relative time until wakeup. */
		TimestampDifference(now, wakeup_time,
							&sec_to_timeout, &microsec_to_timeout);

		sleeptime = sec_to_timeout * 1000 +
			microsec_to_timeout / 1000;
	}

	return sleeptime;
}