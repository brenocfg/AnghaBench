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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_RCNR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_rtc_settime(struct device *dev, struct rtc_time *tm)
{
	unsigned long rtc_count = 0;

	dev_dbg(dev, "set time %02d.%02d.%02d %02d/%02d/%02d\n",
		 tm->tm_year, tm->tm_mon, tm->tm_mday,
		 tm->tm_hour, tm->tm_min, tm->tm_sec);

	rtc_tm_to_time(tm, &rtc_count);
	writel(rtc_count, RTC_RCNR);

	return 0;
}