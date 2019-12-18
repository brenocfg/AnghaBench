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
struct irq_desc {int istate; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int IRQS_PENDING ; 
 int IRQS_REPLAY ; 
 int IRQS_WAITING ; 
 int /*<<< orphan*/  handle_irq_event (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_may_run (struct irq_desc*) ; 
 scalar_t__ irqd_irq_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (struct irq_desc*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void handle_simple_irq(struct irq_desc *desc)
{
	raw_spin_lock(&desc->lock);

	if (!irq_may_run(desc))
		goto out_unlock;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	if (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) {
		desc->istate |= IRQS_PENDING;
		goto out_unlock;
	}

	kstat_incr_irqs_this_cpu(desc);
	handle_irq_event(desc);

out_unlock:
	raw_spin_unlock(&desc->lock);
}