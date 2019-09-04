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
typedef  int u8 ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int HOUR_12 ; 
 int HOUR_AM_PM ; 
 size_t RTC_DATE ; 
 size_t RTC_HOUR ; 
 size_t RTC_MIN ; 
 size_t RTC_MONTH ; 
 size_t RTC_SEC ; 
 size_t RTC_WEEKDAY ; 
 size_t RTC_YEAR1 ; 
 size_t RTC_YEAR2 ; 
 int bcd2bin (int) ; 

__attribute__((used)) static void regs_to_tm(u8 *regs, struct rtc_time *tm)
{
	tm->tm_year = bcd2bin(regs[RTC_YEAR2]) * 100 +
		bcd2bin(regs[RTC_YEAR1]) - 1900;
	tm->tm_mon = bcd2bin(regs[RTC_MONTH] & 0x1f) - 1;
	tm->tm_mday = bcd2bin(regs[RTC_DATE] & 0x3f);
	tm->tm_wday = (regs[RTC_WEEKDAY] & 0x07);
	if (regs[RTC_HOUR] & HOUR_12) {
		tm->tm_hour = bcd2bin(regs[RTC_HOUR] & 0x01f);
		if (tm->tm_hour == 12)
			tm->tm_hour = 0;
		if (regs[RTC_HOUR] & HOUR_AM_PM)
			tm->tm_hour += 12;
	} else {
		tm->tm_hour = bcd2bin(regs[RTC_HOUR] & 0x03f);
	}
	tm->tm_min = bcd2bin(regs[RTC_MIN] & 0x7f);
	tm->tm_sec = bcd2bin(regs[RTC_SEC] & 0x7f);
}