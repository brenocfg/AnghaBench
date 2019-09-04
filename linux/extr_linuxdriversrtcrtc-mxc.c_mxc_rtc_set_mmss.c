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
typedef  scalar_t__ time64_t ;
struct rtc_time {int tm_year; } ;
struct rtc_plat_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_RTC_TIME ; 
 struct rtc_plat_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ get_alarm_or_time (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_imx1_rtc (struct rtc_plat_data*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  set_alarm_or_time (struct device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mxc_rtc_set_mmss(struct device *dev, time64_t time)
{
	struct rtc_plat_data *pdata = dev_get_drvdata(dev);

	/*
	 * TTC_DAYR register is 9-bit in MX1 SoC, save time and day of year only
	 */
	if (is_imx1_rtc(pdata)) {
		struct rtc_time tm;

		rtc_time64_to_tm(time, &tm);
		tm.tm_year = 70;
		time = rtc_tm_to_time64(&tm);
	}

	/* Avoid roll-over from reading the different registers */
	do {
		set_alarm_or_time(dev, MXC_RTC_TIME, time);
	} while (time != get_alarm_or_time(dev, MXC_RTC_TIME));

	return 0;
}