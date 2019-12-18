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
typedef  int int64 ;
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  feTimestampDifference (scalar_t__,scalar_t__,long*,int*) ; 
 scalar_t__ still_sending ; 

__attribute__((used)) static long
CalculateCopyStreamSleeptime(TimestampTz now, int standby_message_timeout,
							 TimestampTz last_status)
{
	TimestampTz status_targettime = 0;
	long		sleeptime;

	if (standby_message_timeout && still_sending)
		status_targettime = last_status +
			(standby_message_timeout - 1) * ((int64) 1000);

	if (status_targettime > 0)
	{
		long		secs;
		int			usecs;

		feTimestampDifference(now,
							  status_targettime,
							  &secs,
							  &usecs);
		/* Always sleep at least 1 sec */
		if (secs <= 0)
		{
			secs = 1;
			usecs = 0;
		}

		sleeptime = secs * 1000 + usecs / 1000;
	}
	else
		sleeptime = -1;

	return sleeptime;
}