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
struct rtc_time {int tm_year; int tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static unsigned long get_elapsed_seconds(int year)
{
	unsigned long secs;
	struct rtc_time tm = {
		.tm_year = year - 1900,
		.tm_mday = 1,
	};

	/*
	 * This function calculates secs from 1970 and not from
	 * 1900, even if we supply the offset from year 1900.
	 */
	rtc_tm_to_time(&tm, &secs);
	return secs;
}