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
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_RTAR ; 
 int /*<<< orphan*/  RTC_RTSR ; 
 int RTC_RTSR_ALE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int,struct rtc_time*) ; 

__attribute__((used)) static int puv3_rtc_getalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rtc_time *alm_tm = &alrm->time;

	rtc_time_to_tm(readl(RTC_RTAR), alm_tm);

	alrm->enabled = readl(RTC_RTSR) & RTC_RTSR_ALE;

	dev_dbg(dev, "read alarm %02x %02x.%02x.%02x %02x/%02x/%02x\n",
		 alrm->enabled,
		 alm_tm->tm_year, alm_tm->tm_mon, alm_tm->tm_mday,
		 alm_tm->tm_hour, alm_tm->tm_min, alm_tm->tm_sec);

	return 0;
}