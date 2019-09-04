#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct omap_rtc {int /*<<< orphan*/  rtc; TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OMAP_RTC_STATUS_1S_EVENT ; 
 int OMAP_RTC_STATUS_ALARM ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_UF ; 
 int rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  rtc_write (struct omap_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 

__attribute__((used)) static irqreturn_t rtc_irq(int irq, void *dev_id)
{
	struct omap_rtc	*rtc = dev_id;
	unsigned long events = 0;
	u8 irq_data;

	irq_data = rtc_read(rtc, OMAP_RTC_STATUS_REG);

	/* alarm irq? */
	if (irq_data & OMAP_RTC_STATUS_ALARM) {
		rtc->type->unlock(rtc);
		rtc_write(rtc, OMAP_RTC_STATUS_REG, OMAP_RTC_STATUS_ALARM);
		rtc->type->lock(rtc);
		events |= RTC_IRQF | RTC_AF;
	}

	/* 1/sec periodic/update irq? */
	if (irq_data & OMAP_RTC_STATUS_1S_EVENT)
		events |= RTC_IRQF | RTC_UF;

	rtc_update_irq(rtc->rtc, 1, events);

	return IRQ_HANDLED;
}