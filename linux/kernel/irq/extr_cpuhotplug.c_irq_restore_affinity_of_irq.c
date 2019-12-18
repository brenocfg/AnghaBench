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
struct irq_desc {int /*<<< orphan*/  action; } ;
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RESEND ; 
 int /*<<< orphan*/  IRQ_START_COND ; 
 int /*<<< orphan*/  cpumask_test_cpu (unsigned int,struct cpumask const*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_set_affinity_locked (struct irq_data*,struct cpumask const*,int) ; 
 int /*<<< orphan*/  irq_startup (struct irq_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_affinity_is_managed (struct irq_data*) ; 
 scalar_t__ irqd_is_managed_and_shutdown (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_single_target (struct irq_data*) ; 

__attribute__((used)) static void irq_restore_affinity_of_irq(struct irq_desc *desc, unsigned int cpu)
{
	struct irq_data *data = irq_desc_get_irq_data(desc);
	const struct cpumask *affinity = irq_data_get_affinity_mask(data);

	if (!irqd_affinity_is_managed(data) || !desc->action ||
	    !irq_data_get_irq_chip(data) || !cpumask_test_cpu(cpu, affinity))
		return;

	if (irqd_is_managed_and_shutdown(data)) {
		irq_startup(desc, IRQ_RESEND, IRQ_START_COND);
		return;
	}

	/*
	 * If the interrupt can only be directed to a single target
	 * CPU then it is already assigned to a CPU in the affinity
	 * mask. No point in trying to move it around.
	 */
	if (!irqd_is_single_target(data))
		irq_set_affinity_locked(data, affinity, false);
}