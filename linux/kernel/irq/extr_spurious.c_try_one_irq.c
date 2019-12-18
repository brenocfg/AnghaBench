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
struct irqaction {int flags; } ;
struct irq_desc {int istate; int /*<<< orphan*/  lock; struct irqaction* action; int /*<<< orphan*/  irq_data; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int IRQS_PENDING ; 
 int IRQS_POLL_INPROGRESS ; 
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int __IRQF_TIMER ; 
 scalar_t__ handle_irq_event (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_nested_thread (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_per_cpu (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_polled (struct irq_desc*) ; 
 scalar_t__ irqd_irq_disabled (int /*<<< orphan*/ *) ; 
 scalar_t__ irqd_irq_inprogress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_one_irq(struct irq_desc *desc, bool force)
{
	irqreturn_t ret = IRQ_NONE;
	struct irqaction *action;

	raw_spin_lock(&desc->lock);

	/*
	 * PER_CPU, nested thread interrupts and interrupts explicitly
	 * marked polled are excluded from polling.
	 */
	if (irq_settings_is_per_cpu(desc) ||
	    irq_settings_is_nested_thread(desc) ||
	    irq_settings_is_polled(desc))
		goto out;

	/*
	 * Do not poll disabled interrupts unless the spurious
	 * disabled poller asks explicitly.
	 */
	if (irqd_irq_disabled(&desc->irq_data) && !force)
		goto out;

	/*
	 * All handlers must agree on IRQF_SHARED, so we test just the
	 * first.
	 */
	action = desc->action;
	if (!action || !(action->flags & IRQF_SHARED) ||
	    (action->flags & __IRQF_TIMER))
		goto out;

	/* Already running on another processor */
	if (irqd_irq_inprogress(&desc->irq_data)) {
		/*
		 * Already running: If it is shared get the other
		 * CPU to go looking for our mystery interrupt too
		 */
		desc->istate |= IRQS_PENDING;
		goto out;
	}

	/* Mark it poll in progress */
	desc->istate |= IRQS_POLL_INPROGRESS;
	do {
		if (handle_irq_event(desc) == IRQ_HANDLED)
			ret = IRQ_HANDLED;
		/* Make sure that there is still a valid action */
		action = desc->action;
	} while ((desc->istate & IRQS_PENDING) && action);
	desc->istate &= ~IRQS_POLL_INPROGRESS;
out:
	raw_spin_unlock(&desc->lock);
	return ret == IRQ_HANDLED;
}