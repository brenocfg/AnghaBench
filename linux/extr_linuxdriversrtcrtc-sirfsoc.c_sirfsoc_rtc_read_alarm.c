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
struct sirfsoc_rtc_drv {int overflow_rtc; int /*<<< orphan*/  lock; } ;
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  RTC_ALARM0 ; 
 int /*<<< orphan*/  RTC_CN ; 
 int RTC_SHIFT ; 
 int /*<<< orphan*/  RTC_STATUS ; 
 int SIRFSOC_RTC_AL0E ; 
 struct sirfsoc_rtc_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memset (struct rtc_wkalrm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int,int /*<<< orphan*/ *) ; 
 int sirfsoc_rtc_readl (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirfsoc_rtc_read_alarm(struct device *dev,
		struct rtc_wkalrm *alrm)
{
	unsigned long rtc_alarm, rtc_count;
	struct sirfsoc_rtc_drv *rtcdrv;

	rtcdrv = dev_get_drvdata(dev);

	spin_lock_irq(&rtcdrv->lock);

	rtc_count = sirfsoc_rtc_readl(rtcdrv, RTC_CN);

	rtc_alarm = sirfsoc_rtc_readl(rtcdrv, RTC_ALARM0);
	memset(alrm, 0, sizeof(struct rtc_wkalrm));

	/*
	 * assume alarm interval not beyond one round counter overflow_rtc:
	 * 0->0xffffffff
	 */
	/* if alarm is in next overflow cycle */
	if (rtc_count > rtc_alarm)
		rtc_time_to_tm((rtcdrv->overflow_rtc + 1)
				<< (BITS_PER_LONG - RTC_SHIFT)
				| rtc_alarm >> RTC_SHIFT, &(alrm->time));
	else
		rtc_time_to_tm(rtcdrv->overflow_rtc
				<< (BITS_PER_LONG - RTC_SHIFT)
				| rtc_alarm >> RTC_SHIFT, &(alrm->time));
	if (sirfsoc_rtc_readl(rtcdrv, RTC_STATUS) & SIRFSOC_RTC_AL0E)
		alrm->enabled = 1;

	spin_unlock_irq(&rtcdrv->lock);

	return 0;
}