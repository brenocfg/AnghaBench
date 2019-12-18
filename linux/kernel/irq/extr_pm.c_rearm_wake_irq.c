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
struct irq_desc {int istate; int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQD_WAKEUP_ARMED ; 
 int IRQS_SUSPENDED ; 
 int /*<<< orphan*/  IRQ_GET_DESC_CHECK_GLOBAL ; 
 int /*<<< orphan*/  __enable_irq (struct irq_desc*) ; 
 struct irq_desc* irq_get_desc_buslock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_busunlock (struct irq_desc*,unsigned long) ; 
 int /*<<< orphan*/  irqd_is_wakeup_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqd_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rearm_wake_irq(unsigned int irq)
{
	unsigned long flags;
	struct irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);

	if (!desc || !(desc->istate & IRQS_SUSPENDED) ||
	    !irqd_is_wakeup_set(&desc->irq_data))
		return;

	desc->istate &= ~IRQS_SUSPENDED;
	irqd_set(&desc->irq_data, IRQD_WAKEUP_ARMED);
	__enable_irq(desc);

	irq_put_desc_busunlock(desc, flags);
}