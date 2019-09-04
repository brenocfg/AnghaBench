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
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int puv3_rtc_gettime(struct device *dev, struct rtc_time *rtc_tm)
{
	rtc_time_to_tm(readl(RTC_RCNR), rtc_tm);

	dev_dbg(dev, "read time %02x.%02x.%02x %02x/%02x/%02x\n",
		 rtc_tm->tm_year, rtc_tm->tm_mon, rtc_tm->tm_mday,
		 rtc_tm->tm_hour, rtc_tm->tm_min, rtc_tm->tm_sec);

	return 0;
}