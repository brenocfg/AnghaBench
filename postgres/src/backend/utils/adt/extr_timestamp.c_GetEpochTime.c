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
struct pg_tm {int tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; } ;
typedef  int /*<<< orphan*/  pg_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 struct pg_tm* pg_gmtime (int /*<<< orphan*/ *) ; 

void
GetEpochTime(struct pg_tm *tm)
{
	struct pg_tm *t0;
	pg_time_t	epoch = 0;

	t0 = pg_gmtime(&epoch);

	if (t0 == NULL)
		elog(ERROR, "could not convert epoch to timestamp: %m");

	tm->tm_year = t0->tm_year;
	tm->tm_mon = t0->tm_mon;
	tm->tm_mday = t0->tm_mday;
	tm->tm_hour = t0->tm_hour;
	tm->tm_min = t0->tm_min;
	tm->tm_sec = t0->tm_sec;

	tm->tm_year += 1900;
	tm->tm_mon++;
}