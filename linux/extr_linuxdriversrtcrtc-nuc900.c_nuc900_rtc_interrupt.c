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
struct nuc900_rtc {int /*<<< orphan*/  rtcdev; scalar_t__ rtc_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long ALARMINTENB ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_RTC_RIIR ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_UF ; 
 unsigned long TICKINTENB ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static irqreturn_t nuc900_rtc_interrupt(int irq, void *_rtc)
{
	struct nuc900_rtc *rtc = _rtc;
	unsigned long events = 0, rtc_irq;

	rtc_irq = __raw_readl(rtc->rtc_reg + REG_RTC_RIIR);

	if (rtc_irq & ALARMINTENB) {
		rtc_irq &= ~ALARMINTENB;
		__raw_writel(rtc_irq, rtc->rtc_reg + REG_RTC_RIIR);
		events |= RTC_AF | RTC_IRQF;
	}

	if (rtc_irq & TICKINTENB) {
		rtc_irq &= ~TICKINTENB;
		__raw_writel(rtc_irq, rtc->rtc_reg + REG_RTC_RIIR);
		events |= RTC_UF | RTC_IRQF;
	}

	rtc_update_irq(rtc->rtcdev, 1, events);

	return IRQ_HANDLED;
}