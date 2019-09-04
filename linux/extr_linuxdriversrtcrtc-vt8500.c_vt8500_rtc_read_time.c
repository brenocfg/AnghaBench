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
typedef  int u32 ;
struct vt8500_rtc {scalar_t__ regbase; } ;
struct rtc_time {int tm_wday; void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DATE_CENTURY_S ; 
 int DATE_DAY_MASK ; 
 int DATE_MONTH_MASK ; 
 int DATE_MONTH_S ; 
 int DATE_YEAR_MASK ; 
 int DATE_YEAR_S ; 
 int TIME_DOW_MASK ; 
 int TIME_DOW_S ; 
 int TIME_HOUR_MASK ; 
 int TIME_HOUR_S ; 
 int TIME_MIN_MASK ; 
 int TIME_MIN_S ; 
 int TIME_SEC_MASK ; 
 scalar_t__ VT8500_RTC_DR ; 
 scalar_t__ VT8500_RTC_TR ; 
 void* bcd2bin (int) ; 
 struct vt8500_rtc* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int vt8500_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);
	u32 date, time;

	date = readl(vt8500_rtc->regbase + VT8500_RTC_DR);
	time = readl(vt8500_rtc->regbase + VT8500_RTC_TR);

	tm->tm_sec = bcd2bin(time & TIME_SEC_MASK);
	tm->tm_min = bcd2bin((time & TIME_MIN_MASK) >> TIME_MIN_S);
	tm->tm_hour = bcd2bin((time & TIME_HOUR_MASK) >> TIME_HOUR_S);
	tm->tm_mday = bcd2bin(date & DATE_DAY_MASK);
	tm->tm_mon = bcd2bin((date & DATE_MONTH_MASK) >> DATE_MONTH_S) - 1;
	tm->tm_year = bcd2bin((date & DATE_YEAR_MASK) >> DATE_YEAR_S)
			+ ((date >> DATE_CENTURY_S) & 1 ? 200 : 100);
	tm->tm_wday = (time & TIME_DOW_MASK) >> TIME_DOW_S;

	return 0;
}