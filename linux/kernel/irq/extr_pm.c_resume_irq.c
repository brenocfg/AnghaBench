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
struct irq_desc {int istate; int /*<<< orphan*/  depth; int /*<<< orphan*/  force_resume_depth; int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQD_WAKEUP_ARMED ; 
 int IRQS_SUSPENDED ; 
 int /*<<< orphan*/  __enable_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_state_set_disabled (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_state_set_masked (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resume_irq(struct irq_desc *desc)
{
	irqd_clear(&desc->irq_data, IRQD_WAKEUP_ARMED);

	if (desc->istate & IRQS_SUSPENDED)
		goto resume;

	/* Force resume the interrupt? */
	if (!desc->force_resume_depth)
		return;

	/* Pretend that it got disabled ! */
	desc->depth++;
	irq_state_set_disabled(desc);
	irq_state_set_masked(desc);
resume:
	desc->istate &= ~IRQS_SUSPENDED;
	__enable_irq(desc);
}