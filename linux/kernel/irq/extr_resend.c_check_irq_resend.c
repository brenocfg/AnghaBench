#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* chip; } ;
struct irq_desc {int istate; unsigned int parent_irq; TYPE_2__ irq_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_retrigger ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int IRQS_PENDING ; 
 int IRQS_REPLAY ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_level (struct irq_desc*) ; 
 scalar_t__ irq_settings_is_nested_thread (struct irq_desc*) ; 
 int /*<<< orphan*/  irqs_resend ; 
 int /*<<< orphan*/  resend_tasklet ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void check_irq_resend(struct irq_desc *desc)
{
	/*
	 * We do not resend level type interrupts. Level type
	 * interrupts are resent by hardware when they are still
	 * active. Clear the pending bit so suspend/resume does not
	 * get confused.
	 */
	if (irq_settings_is_level(desc)) {
		desc->istate &= ~IRQS_PENDING;
		return;
	}
	if (desc->istate & IRQS_REPLAY)
		return;
	if (desc->istate & IRQS_PENDING) {
		desc->istate &= ~IRQS_PENDING;
		desc->istate |= IRQS_REPLAY;

		if (!desc->irq_data.chip->irq_retrigger ||
		    !desc->irq_data.chip->irq_retrigger(&desc->irq_data)) {
#ifdef CONFIG_HARDIRQS_SW_RESEND
			unsigned int irq = irq_desc_get_irq(desc);

			/*
			 * If the interrupt is running in the thread
			 * context of the parent irq we need to be
			 * careful, because we cannot trigger it
			 * directly.
			 */
			if (irq_settings_is_nested_thread(desc)) {
				/*
				 * If the parent_irq is valid, we
				 * retrigger the parent, otherwise we
				 * do nothing.
				 */
				if (!desc->parent_irq)
					return;
				irq = desc->parent_irq;
			}
			/* Set it pending and activate the softirq: */
			set_bit(irq, irqs_resend);
			tasklet_schedule(&resend_tasklet);
#endif
		}
	}
}