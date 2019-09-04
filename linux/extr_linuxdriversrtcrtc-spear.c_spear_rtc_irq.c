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
struct spear_rtc_config {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; scalar_t__ ioaddr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long RTC_AF ; 
 unsigned int RTC_INT_MASK ; 
 unsigned long RTC_IRQF ; 
 scalar_t__ STATUS_REG ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  spear_rtc_clear_interrupt (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t spear_rtc_irq(int irq, void *dev_id)
{
	struct spear_rtc_config *config = dev_id;
	unsigned long flags, events = 0;
	unsigned int irq_data;

	spin_lock_irqsave(&config->lock, flags);
	irq_data = readl(config->ioaddr + STATUS_REG);
	spin_unlock_irqrestore(&config->lock, flags);

	if ((irq_data & RTC_INT_MASK)) {
		spear_rtc_clear_interrupt(config);
		events = RTC_IRQF | RTC_AF;
		rtc_update_irq(config->rtc, 1, events);
		return IRQ_HANDLED;
	} else
		return IRQ_NONE;

}