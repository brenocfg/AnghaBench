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
struct sirfsoc_rtc_drv {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_STATUS ; 
 unsigned long SIRFSOC_RTC_AL0E ; 
 struct sirfsoc_rtc_drv* dev_get_drvdata (struct device*) ; 
 unsigned long sirfsoc_rtc_readl (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_rtc_writel (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirfsoc_rtc_alarm_irq_enable(struct device *dev,
		unsigned int enabled)
{
	unsigned long rtc_status_reg = 0x0;
	struct sirfsoc_rtc_drv *rtcdrv;

	rtcdrv = dev_get_drvdata(dev);

	spin_lock_irq(&rtcdrv->lock);

	rtc_status_reg = sirfsoc_rtc_readl(rtcdrv, RTC_STATUS);
	if (enabled)
		rtc_status_reg |= SIRFSOC_RTC_AL0E;
	else
		rtc_status_reg &= ~SIRFSOC_RTC_AL0E;

	sirfsoc_rtc_writel(rtcdrv, RTC_STATUS, rtc_status_reg);

	spin_unlock_irq(&rtcdrv->lock);

	return 0;

}