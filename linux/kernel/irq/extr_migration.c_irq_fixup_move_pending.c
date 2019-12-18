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
struct irq_desc {int /*<<< orphan*/  pending_mask; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 scalar_t__ cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_clr_move_pending (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_setaffinity_pending (struct irq_data*) ; 
 scalar_t__ nr_cpu_ids ; 

bool irq_fixup_move_pending(struct irq_desc *desc, bool force_clear)
{
	struct irq_data *data = irq_desc_get_irq_data(desc);

	if (!irqd_is_setaffinity_pending(data))
		return false;

	/*
	 * The outgoing CPU might be the last online target in a pending
	 * interrupt move. If that's the case clear the pending move bit.
	 */
	if (cpumask_any_and(desc->pending_mask, cpu_online_mask) >= nr_cpu_ids) {
		irqd_clr_move_pending(data);
		return false;
	}
	if (force_clear)
		irqd_clr_move_pending(data);
	return true;
}