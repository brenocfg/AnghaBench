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
struct pic32_rtc_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_rtc_alarm_clk_enable (struct pic32_rtc_dev*,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t pic32_rtc_alarmirq(int irq, void *id)
{
	struct pic32_rtc_dev *pdata = (struct pic32_rtc_dev *)id;

	clk_enable(pdata->clk);
	rtc_update_irq(pdata->rtc, 1, RTC_AF | RTC_IRQF);
	clk_disable(pdata->clk);

	pic32_rtc_alarm_clk_enable(pdata, false);

	return IRQ_HANDLED;
}