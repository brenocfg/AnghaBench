#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timestamp ;
struct tm {int tm_mon; int tm_year; scalar_t__ tm_mday; } ;
struct TYPE_3__ {scalar_t__ month; scalar_t__ time; } ;
typedef  TYPE_1__ interval ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int MONTHS_PER_YEAR ; 
 scalar_t__ TIMESTAMP_NOT_FINITE (int /*<<< orphan*/ ) ; 
 scalar_t__** day_tab ; 
 size_t isleap (int) ; 
 scalar_t__ timestamp2tm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tm2timestamp (struct tm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
PGTYPEStimestamp_add_interval(timestamp * tin, interval * span, timestamp * tout)
{
	if (TIMESTAMP_NOT_FINITE(*tin))
		*tout = *tin;


	else
	{
		if (span->month != 0)
		{
			struct tm	tt,
					   *tm = &tt;
			fsec_t		fsec;


			if (timestamp2tm(*tin, NULL, tm, &fsec, NULL) != 0)
				return -1;
			tm->tm_mon += span->month;
			if (tm->tm_mon > MONTHS_PER_YEAR)
			{
				tm->tm_year += (tm->tm_mon - 1) / MONTHS_PER_YEAR;
				tm->tm_mon = (tm->tm_mon - 1) % MONTHS_PER_YEAR + 1;
			}
			else if (tm->tm_mon < 1)
			{
				tm->tm_year += tm->tm_mon / MONTHS_PER_YEAR - 1;
				tm->tm_mon = tm->tm_mon % MONTHS_PER_YEAR + MONTHS_PER_YEAR;
			}


			/* adjust for end of month boundary problems... */
			if (tm->tm_mday > day_tab[isleap(tm->tm_year)][tm->tm_mon - 1])
				tm->tm_mday = (day_tab[isleap(tm->tm_year)][tm->tm_mon - 1]);


			if (tm2timestamp(tm, fsec, NULL, tin) != 0)
				return -1;
		}


		*tin += span->time;
		*tout = *tin;
	}
	return 0;

}