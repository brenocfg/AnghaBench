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
struct irq_desc {int dummy; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_unmask ) (struct irq_data*) ;int /*<<< orphan*/  (* irq_mask ) (struct irq_data*) ;int /*<<< orphan*/  irq_set_affinity; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 struct cpumask* cpu_online_mask ; 
 scalar_t__ cpumask_any_and (struct cpumask const*,struct cpumask*) ; 
 int /*<<< orphan*/  irq_can_move_pcntxt (struct irq_data*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 struct cpumask* irq_desc_get_pending_mask (struct irq_desc*) ; 
 int irq_do_set_affinity (struct irq_data*,struct cpumask const*,int) ; 
 scalar_t__ irq_fixup_move_pending (struct irq_desc*,int) ; 
 int /*<<< orphan*/  irq_force_complete_move (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_needs_fixup (struct irq_data*) ; 
 int /*<<< orphan*/  irq_shutdown_and_deactivate (struct irq_desc*) ; 
 scalar_t__ irqd_affinity_is_managed (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_irq_masked (struct irq_data*) ; 
 scalar_t__ irqd_is_per_cpu (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_started (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_set_managed_shutdown (struct irq_data*) ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 
 int /*<<< orphan*/  stub2 (struct irq_data*) ; 

__attribute__((used)) static bool migrate_one_irq(struct irq_desc *desc)
{
	struct irq_data *d = irq_desc_get_irq_data(desc);
	struct irq_chip *chip = irq_data_get_irq_chip(d);
	bool maskchip = !irq_can_move_pcntxt(d) && !irqd_irq_masked(d);
	const struct cpumask *affinity;
	bool brokeaff = false;
	int err;

	/*
	 * IRQ chip might be already torn down, but the irq descriptor is
	 * still in the radix tree. Also if the chip has no affinity setter,
	 * nothing can be done here.
	 */
	if (!chip || !chip->irq_set_affinity) {
		pr_debug("IRQ %u: Unable to migrate away\n", d->irq);
		return false;
	}

	/*
	 * No move required, if:
	 * - Interrupt is per cpu
	 * - Interrupt is not started
	 * - Affinity mask does not include this CPU.
	 *
	 * Note: Do not check desc->action as this might be a chained
	 * interrupt.
	 */
	if (irqd_is_per_cpu(d) || !irqd_is_started(d) || !irq_needs_fixup(d)) {
		/*
		 * If an irq move is pending, abort it if the dying CPU is
		 * the sole target.
		 */
		irq_fixup_move_pending(desc, false);
		return false;
	}

	/*
	 * Complete an eventually pending irq move cleanup. If this
	 * interrupt was moved in hard irq context, then the vectors need
	 * to be cleaned up. It can't wait until this interrupt actually
	 * happens and this CPU was involved.
	 */
	irq_force_complete_move(desc);

	/*
	 * If there is a setaffinity pending, then try to reuse the pending
	 * mask, so the last change of the affinity does not get lost. If
	 * there is no move pending or the pending mask does not contain
	 * any online CPU, use the current affinity mask.
	 */
	if (irq_fixup_move_pending(desc, true))
		affinity = irq_desc_get_pending_mask(desc);
	else
		affinity = irq_data_get_affinity_mask(d);

	/* Mask the chip for interrupts which cannot move in process context */
	if (maskchip && chip->irq_mask)
		chip->irq_mask(d);

	if (cpumask_any_and(affinity, cpu_online_mask) >= nr_cpu_ids) {
		/*
		 * If the interrupt is managed, then shut it down and leave
		 * the affinity untouched.
		 */
		if (irqd_affinity_is_managed(d)) {
			irqd_set_managed_shutdown(d);
			irq_shutdown_and_deactivate(desc);
			return false;
		}
		affinity = cpu_online_mask;
		brokeaff = true;
	}
	/*
	 * Do not set the force argument of irq_do_set_affinity() as this
	 * disables the masking of offline CPUs from the supplied affinity
	 * mask and therefore might keep/reassign the irq to the outgoing
	 * CPU.
	 */
	err = irq_do_set_affinity(d, affinity, false);
	if (err) {
		pr_warn_ratelimited("IRQ%u: set affinity failed(%d).\n",
				    d->irq, err);
		brokeaff = false;
	}

	if (maskchip && chip->irq_unmask)
		chip->irq_unmask(d);

	return brokeaff;
}