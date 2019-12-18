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
struct tm {double tm_year; scalar_t__ tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_3__ {scalar_t__ month; scalar_t__ time; } ;
typedef  TYPE_1__ interval ;
typedef  scalar_t__ fsec_t ;

/* Variables and functions */
 int INT64CONST (int) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 double MONTHS_PER_YEAR ; 
 int USECS_PER_SEC ; 

__attribute__((used)) static int
tm2interval(struct tm *tm, fsec_t fsec, interval * span)
{
	if ((double) tm->tm_year * MONTHS_PER_YEAR + tm->tm_mon > INT_MAX ||
		(double) tm->tm_year * MONTHS_PER_YEAR + tm->tm_mon < INT_MIN)
		return -1;
	span->month = tm->tm_year * MONTHS_PER_YEAR + tm->tm_mon;
	span->time = (((((((tm->tm_mday * INT64CONST(24)) +
					   tm->tm_hour) * INT64CONST(60)) +
					 tm->tm_min) * INT64CONST(60)) +
				   tm->tm_sec) * USECS_PER_SEC) + fsec;

	return 0;
}