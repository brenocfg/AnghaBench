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
struct rtc_time {int tm_mday; int tm_mon; int tm_year; int tm_hour; int tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_RTAR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puv3_rtc_alarmno ; 
 int /*<<< orphan*/  puv3_rtc_setaie (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rtc_time *tm = &alrm->time;
	unsigned long rtcalarm_count = 0;

	dev_dbg(dev, "puv3_rtc_setalarm: %d, %02x/%02x/%02x %02x.%02x.%02x\n",
		 alrm->enabled,
		 tm->tm_mday & 0xff, tm->tm_mon & 0xff, tm->tm_year & 0xff,
		 tm->tm_hour & 0xff, tm->tm_min & 0xff, tm->tm_sec);

	rtc_tm_to_time(tm, &rtcalarm_count);
	writel(rtcalarm_count, RTC_RTAR);

	puv3_rtc_setaie(dev, alrm->enabled);

	if (alrm->enabled)
		enable_irq_wake(puv3_rtc_alarmno);
	else
		disable_irq_wake(puv3_rtc_alarmno);

	return 0;
}