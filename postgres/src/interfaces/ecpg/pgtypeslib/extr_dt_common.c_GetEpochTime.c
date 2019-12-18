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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/ *) ; 

int
GetEpochTime(struct tm *tm)
{
	struct tm  *t0;
	time_t		epoch = 0;

	t0 = gmtime(&epoch);

	if (t0)
	{
		tm->tm_year = t0->tm_year + 1900;
		tm->tm_mon = t0->tm_mon + 1;
		tm->tm_mday = t0->tm_mday;
		tm->tm_hour = t0->tm_hour;
		tm->tm_min = t0->tm_min;
		tm->tm_sec = t0->tm_sec;

		return 0;
	}

	return -1;
}