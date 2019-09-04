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
typedef  int /*<<< orphan*/  time64_t ;
struct rtc_time {int tm_wday; unsigned int tm_year; int tm_yday; unsigned int tm_mon; int tm_mday; unsigned int tm_hour; unsigned int tm_min; unsigned int tm_sec; scalar_t__ tm_isdst; } ;

/* Variables and functions */
 scalar_t__ LEAPS_THRU_END_OF (int) ; 
 int div_s64_rem (int /*<<< orphan*/ ,int,unsigned int*) ; 
 scalar_t__ is_leap_year (unsigned int) ; 
 int rtc_month_days (unsigned int,unsigned int) ; 

void rtc_time64_to_tm(time64_t time, struct rtc_time *tm)
{
	unsigned int month, year, secs;
	int days;

	/* time must be positive */
	days = div_s64_rem(time, 86400, &secs);

	/* day of the week, 1970-01-01 was a Thursday */
	tm->tm_wday = (days + 4) % 7;

	year = 1970 + days / 365;
	days -= (year - 1970) * 365
		+ LEAPS_THRU_END_OF(year - 1)
		- LEAPS_THRU_END_OF(1970 - 1);
	while (days < 0) {
		year -= 1;
		days += 365 + is_leap_year(year);
	}
	tm->tm_year = year - 1900;
	tm->tm_yday = days + 1;

	for (month = 0; month < 11; month++) {
		int newdays;

		newdays = days - rtc_month_days(month, year);
		if (newdays < 0)
			break;
		days = newdays;
	}
	tm->tm_mon = month;
	tm->tm_mday = days + 1;

	tm->tm_hour = secs / 3600;
	secs -= tm->tm_hour * 3600;
	tm->tm_min = secs / 60;
	tm->tm_sec = secs - tm->tm_min * 60;

	tm->tm_isdst = 0;
}