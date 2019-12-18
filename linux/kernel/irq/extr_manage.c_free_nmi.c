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
struct irq_desc {int istate; scalar_t__ depth; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int IRQS_NMI ; 
 scalar_t__ WARN_ON (int) ; 
 void* __cleanup_nmi (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  disable_nmi_nosync (unsigned int) ; 
 int /*<<< orphan*/  irq_nmi_teardown (struct irq_desc*) ; 
 int irq_settings_is_per_cpu_devid (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

const void *free_nmi(unsigned int irq, void *dev_id)
{
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned long flags;
	const void *devname;

	if (!desc || WARN_ON(!(desc->istate & IRQS_NMI)))
		return NULL;

	if (WARN_ON(irq_settings_is_per_cpu_devid(desc)))
		return NULL;

	/* NMI still enabled */
	if (WARN_ON(desc->depth == 0))
		disable_nmi_nosync(irq);

	raw_spin_lock_irqsave(&desc->lock, flags);

	irq_nmi_teardown(desc);
	devname = __cleanup_nmi(irq, desc);

	raw_spin_unlock_irqrestore(&desc->lock, flags);

	return devname;
}