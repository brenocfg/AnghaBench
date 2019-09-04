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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 
 unsigned long rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static void rtc_next_alarm_time(struct rtc_time *next, struct rtc_time *now,
				struct rtc_time *alrm)
{
	unsigned long next_time;
	unsigned long now_time;

	next->tm_year = now->tm_year;
	next->tm_mon = now->tm_mon;
	next->tm_mday = now->tm_mday;
	next->tm_hour = alrm->tm_hour;
	next->tm_min = alrm->tm_min;
	next->tm_sec = alrm->tm_sec;

	now_time = rtc_tm_to_time64(now);
	next_time = rtc_tm_to_time64(next);

	if (next_time < now_time) {
		/* Advance one day */
		next_time += 60 * 60 * 24;
		rtc_time64_to_tm(next_time, next);
	}
}