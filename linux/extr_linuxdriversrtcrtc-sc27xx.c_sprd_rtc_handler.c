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
struct sprd_rtc {int /*<<< orphan*/  rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int sprd_rtc_clear_alarm_ints (struct sprd_rtc*) ; 

__attribute__((used)) static irqreturn_t sprd_rtc_handler(int irq, void *dev_id)
{
	struct sprd_rtc *rtc = dev_id;
	int ret;

	ret = sprd_rtc_clear_alarm_ints(rtc);
	if (ret)
		return IRQ_RETVAL(ret);

	rtc_update_irq(rtc->rtc, 1, RTC_AF | RTC_IRQF);
	return IRQ_HANDLED;
}