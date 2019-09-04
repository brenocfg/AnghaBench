#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* chip; } ;
struct irq_desc {int istate; int /*<<< orphan*/  lock; TYPE_2__ irq_data; int /*<<< orphan*/  action; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq_ack ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int IRQS_PENDING ; 
 int IRQS_REPLAY ; 
 int IRQS_WAITING ; 
 int /*<<< orphan*/  handle_irq_event (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_may_run (struct irq_desc*) ; 
 scalar_t__ irqd_irq_disabled (TYPE_2__*) ; 
 scalar_t__ irqd_irq_masked (TYPE_2__*) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (struct irq_desc*) ; 
 int /*<<< orphan*/  mask_ack_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  mask_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmask_irq (struct irq_desc*) ; 

void handle_edge_irq(struct irq_desc *desc)
{
	raw_spin_lock(&desc->lock);

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	if (!irq_may_run(desc)) {
		desc->istate |= IRQS_PENDING;
		mask_ack_irq(desc);
		goto out_unlock;
	}

	/*
	 * If its disabled or no action available then mask it and get
	 * out of here.
	 */
	if (irqd_irq_disabled(&desc->irq_data) || !desc->action) {
		desc->istate |= IRQS_PENDING;
		mask_ack_irq(desc);
		goto out_unlock;
	}

	kstat_incr_irqs_this_cpu(desc);

	/* Start handling the irq */
	desc->irq_data.chip->irq_ack(&desc->irq_data);

	do {
		if (unlikely(!desc->action)) {
			mask_irq(desc);
			goto out_unlock;
		}

		/*
		 * When another irq arrived while we were handling
		 * one, we could have masked the irq.
		 * Renable it, if it was not disabled in meantime.
		 */
		if (unlikely(desc->istate & IRQS_PENDING)) {
			if (!irqd_irq_disabled(&desc->irq_data) &&
			    irqd_irq_masked(&desc->irq_data))
				unmask_irq(desc);
		}

		handle_irq_event(desc);

	} while ((desc->istate & IRQS_PENDING) &&
		 !irqd_irq_disabled(&desc->irq_data));

out_unlock:
	raw_spin_unlock(&desc->lock);
}