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
typedef  int time64_t ;
struct rtc_time {int tm_mon; int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 int nov2dec_transitions (struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,struct rtc_time*) ; 
 int rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static void gregorian_to_rockchip(struct rtc_time *tm)
{
	time64_t extra_days = nov2dec_transitions(tm);
	time64_t time = rtc_tm_to_time64(tm);
	rtc_time64_to_tm(time - extra_days * 86400, tm);

	/* Compensate if we went back over Nov 31st (will work up to 2381) */
	if (nov2dec_transitions(tm) < extra_days) {
		if (tm->tm_mon + 1 == 11)
			tm->tm_mday++;	/* This may result in 31! */
		else
			rtc_time64_to_tm(time - (extra_days - 1) * 86400, tm);
	}
}