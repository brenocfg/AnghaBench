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
struct irq_desc {int istate; } ;

/* Variables and functions */
 int IRQS_NMI ; 
 int /*<<< orphan*/  IRQ_GET_DESC_CHECK_PERCPU ; 
 scalar_t__ WARN_ON (int) ; 
 struct irq_desc* irq_get_desc_lock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_nmi_teardown (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_put_desc_unlock (struct irq_desc*,unsigned long) ; 
 int preemptible () ; 

void teardown_percpu_nmi(unsigned int irq)
{
	unsigned long flags;
	struct irq_desc *desc;

	WARN_ON(preemptible());

	desc = irq_get_desc_lock(irq, &flags,
				 IRQ_GET_DESC_CHECK_PERCPU);
	if (!desc)
		return;

	if (WARN_ON(!(desc->istate & IRQS_NMI)))
		goto out;

	irq_nmi_teardown(desc);
out:
	irq_put_desc_unlock(desc, flags);
}