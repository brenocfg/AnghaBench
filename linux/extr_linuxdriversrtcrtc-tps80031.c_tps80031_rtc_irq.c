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
struct tps80031_rtc {int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int clear_alarm_int_status (struct device*,struct tps80031_rtc*) ; 
 struct tps80031_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t tps80031_rtc_irq(int irq, void *data)
{
	struct device *dev = data;
	struct tps80031_rtc *rtc = dev_get_drvdata(dev);
	int ret;

	ret = clear_alarm_int_status(dev, rtc);
	if (ret < 0)
		return ret;

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);
	return IRQ_HANDLED;
}