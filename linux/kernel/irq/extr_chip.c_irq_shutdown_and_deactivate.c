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
struct irq_desc {int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_deactivate_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_shutdown (struct irq_desc*) ; 

void irq_shutdown_and_deactivate(struct irq_desc *desc)
{
	irq_shutdown(desc);
	/*
	 * This must be called even if the interrupt was never started up,
	 * because the activation can happen before the interrupt is
	 * available for request/startup. It has it's own state tracking so
	 * it's safe to call it unconditionally.
	 */
	irq_domain_deactivate_irq(&desc->irq_data);
}