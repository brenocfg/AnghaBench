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
struct irq_data {struct irq_chip* chip; } ;
struct irq_desc {int /*<<< orphan*/  pending_mask; int /*<<< orphan*/  lock; struct irq_data irq_data; } ;
struct irq_chip {int /*<<< orphan*/  irq_set_affinity; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_raw_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 scalar_t__ cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_data_to_desc (struct irq_data*) ; 
 int irq_do_set_affinity (struct irq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irqd_clr_move_pending (struct irq_data*) ; 
 scalar_t__ irqd_is_per_cpu (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_setaffinity_pending (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_set_move_pending (struct irq_data*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ nr_cpu_ids ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void irq_move_masked_irq(struct irq_data *idata)
{
	struct irq_desc *desc = irq_data_to_desc(idata);
	struct irq_data *data = &desc->irq_data;
	struct irq_chip *chip = data->chip;

	if (likely(!irqd_is_setaffinity_pending(data)))
		return;

	irqd_clr_move_pending(data);

	/*
	 * Paranoia: cpu-local interrupts shouldn't be calling in here anyway.
	 */
	if (irqd_is_per_cpu(data)) {
		WARN_ON(1);
		return;
	}

	if (unlikely(cpumask_empty(desc->pending_mask)))
		return;

	if (!chip->irq_set_affinity)
		return;

	assert_raw_spin_locked(&desc->lock);

	/*
	 * If there was a valid mask to work with, please
	 * do the disable, re-program, enable sequence.
	 * This is *not* particularly important for level triggered
	 * but in a edge trigger case, we might be setting rte
	 * when an active trigger is coming in. This could
	 * cause some ioapics to mal-function.
	 * Being paranoid i guess!
	 *
	 * For correct operation this depends on the caller
	 * masking the irqs.
	 */
	if (cpumask_any_and(desc->pending_mask, cpu_online_mask) < nr_cpu_ids) {
		int ret;

		ret = irq_do_set_affinity(data, desc->pending_mask, false);
		/*
		 * If the there is a cleanup pending in the underlying
		 * vector management, reschedule the move for the next
		 * interrupt. Leave desc->pending_mask intact.
		 */
		if (ret == -EBUSY) {
			irqd_set_move_pending(data);
			return;
		}
	}
	cpumask_clear(desc->pending_mask);
}