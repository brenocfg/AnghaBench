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
struct pg_tm {double tm_mon; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  tm_mday; scalar_t__ tm_year; } ;
typedef  scalar_t__ fsec_t ;
struct TYPE_3__ {double month; scalar_t__ time; int /*<<< orphan*/  day; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 int INT64CONST (int) ; 
 double INT_MAX ; 
 double INT_MIN ; 
 double MONTHS_PER_YEAR ; 
 int USECS_PER_SEC ; 

int
tm2interval(struct pg_tm *tm, fsec_t fsec, Interval *span)
{
	double		total_months = (double) tm->tm_year * MONTHS_PER_YEAR + tm->tm_mon;

	if (total_months > INT_MAX || total_months < INT_MIN)
		return -1;
	span->month = total_months;
	span->day = tm->tm_mday;
	span->time = (((((tm->tm_hour * INT64CONST(60)) +
					 tm->tm_min) * INT64CONST(60)) +
				   tm->tm_sec) * USECS_PER_SEC) + fsec;

	return 0;
}