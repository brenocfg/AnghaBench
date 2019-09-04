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
struct dc_rtc {int /*<<< orphan*/  rtc_dev; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DC_RTC_INTFLAG_CLEAR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t dc_rtc_irq(int irq, void *dev_id)
{
	struct dc_rtc *rtc = dev_id;

	writeb_relaxed(1, rtc->regs + DC_RTC_INTFLAG_CLEAR);
	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);

	return IRQ_HANDLED;
}