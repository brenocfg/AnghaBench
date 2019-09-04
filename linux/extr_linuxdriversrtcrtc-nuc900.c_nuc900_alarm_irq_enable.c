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
struct nuc900_rtc {scalar_t__ rtc_reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALARMINTENB ; 
 scalar_t__ REG_RTC_RIER ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 struct nuc900_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int nuc900_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct nuc900_rtc *rtc = dev_get_drvdata(dev);

	if (enabled)
		__raw_writel(__raw_readl(rtc->rtc_reg + REG_RTC_RIER)|
				(ALARMINTENB), rtc->rtc_reg + REG_RTC_RIER);
	else
		__raw_writel(__raw_readl(rtc->rtc_reg + REG_RTC_RIER)&
				(~ALARMINTENB), rtc->rtc_reg + REG_RTC_RIER);

	return 0;
}