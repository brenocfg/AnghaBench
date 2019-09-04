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
struct rtc_time {int tm_year; unsigned long tm_mon; unsigned long tm_mday; unsigned long tm_wday; unsigned long tm_hour; unsigned long tm_min; unsigned long tm_sec; int /*<<< orphan*/  tm_yday; } ;

/* Variables and functions */
 unsigned long RTC_HOUR_MASK ; 
 unsigned long RTC_HOUR_SHIFT ; 
 unsigned long RTC_MDAY_MASK ; 
 unsigned long RTC_MDAY_SHIFT ; 
 unsigned long RTC_MIN_MASK ; 
 unsigned long RTC_MIN_SHIFT ; 
 unsigned long RTC_MON_MASK ; 
 unsigned long RTC_MON_SHIFT ; 
 unsigned long RTC_SEC_MASK ; 
 unsigned long RTC_SEC_SHIFT ; 
 unsigned long RTC_WDAY_MASK ; 
 unsigned long RTC_WDAY_SHIFT ; 
 int bcd2bin (unsigned long) ; 
 int /*<<< orphan*/  rtc_year_days (unsigned long,unsigned long,int) ; 

__attribute__((used)) static int pl031_stv2_time_to_tm(unsigned long st_time, unsigned long bcd_year,
	struct rtc_time *tm)
{
	tm->tm_year = bcd2bin(bcd_year) + (bcd2bin(bcd_year >> 8) * 100);
	tm->tm_mon  = ((st_time & RTC_MON_MASK) >> RTC_MON_SHIFT) - 1;
	tm->tm_mday = ((st_time & RTC_MDAY_MASK) >> RTC_MDAY_SHIFT);
	tm->tm_wday = ((st_time & RTC_WDAY_MASK) >> RTC_WDAY_SHIFT) - 1;
	tm->tm_hour = ((st_time & RTC_HOUR_MASK) >> RTC_HOUR_SHIFT);
	tm->tm_min  = ((st_time & RTC_MIN_MASK) >> RTC_MIN_SHIFT);
	tm->tm_sec  = ((st_time & RTC_SEC_MASK) >> RTC_SEC_SHIFT);

	tm->tm_yday = rtc_year_days(tm->tm_mday, tm->tm_mon, tm->tm_year);
	tm->tm_year -= 1900;

	return 0;
}