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
 int /*<<< orphan*/  GetXLogReceiptTime (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TimestampTzPlusMilliseconds (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ max_standby_archive_delay ; 
 scalar_t__ max_standby_streaming_delay ; 

__attribute__((used)) static TimestampTz
GetStandbyLimitTime(void)
{
	TimestampTz rtime;
	bool		fromStream;

	/*
	 * The cutoff time is the last WAL data receipt time plus the appropriate
	 * delay variable.  Delay of -1 means wait forever.
	 */
	GetXLogReceiptTime(&rtime, &fromStream);
	if (fromStream)
	{
		if (max_standby_streaming_delay < 0)
			return 0;			/* wait forever */
		return TimestampTzPlusMilliseconds(rtime, max_standby_streaming_delay);
	}
	else
	{
		if (max_standby_archive_delay < 0)
			return 0;			/* wait forever */
		return TimestampTzPlusMilliseconds(rtime, max_standby_archive_delay);
	}
}