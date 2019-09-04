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
struct irq_desc {int istate; int /*<<< orphan*/  depth; int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQD_WAKEUP_ARMED ; 
 int IRQS_PENDING ; 
 int IRQS_SUSPENDED ; 
 int /*<<< orphan*/  irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_disable (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_is_wakeup_armed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_system_irq_wakeup (int /*<<< orphan*/ ) ; 

bool irq_pm_check_wakeup(struct irq_desc *desc)
{
	if (irqd_is_wakeup_armed(&desc->irq_data)) {
		irqd_clear(&desc->irq_data, IRQD_WAKEUP_ARMED);
		desc->istate |= IRQS_SUSPENDED | IRQS_PENDING;
		desc->depth++;
		irq_disable(desc);
		pm_system_irq_wakeup(irq_desc_get_irq(desc));
		return true;
	}
	return false;
}