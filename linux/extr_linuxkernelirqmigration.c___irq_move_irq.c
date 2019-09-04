#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_unmask ) (struct irq_data*) ;int /*<<< orphan*/  (* irq_mask ) (struct irq_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  irq_data_to_desc (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_move_masked_irq (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_irq_disabled (struct irq_data*) ; 
 int irqd_irq_masked (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 
 int /*<<< orphan*/  stub2 (struct irq_data*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __irq_move_irq(struct irq_data *idata)
{
	bool masked;

	/*
	 * Get top level irq_data when CONFIG_IRQ_DOMAIN_HIERARCHY is enabled,
	 * and it should be optimized away when CONFIG_IRQ_DOMAIN_HIERARCHY is
	 * disabled. So we avoid an "#ifdef CONFIG_IRQ_DOMAIN_HIERARCHY" here.
	 */
	idata = irq_desc_get_irq_data(irq_data_to_desc(idata));

	if (unlikely(irqd_irq_disabled(idata)))
		return;

	/*
	 * Be careful vs. already masked interrupts. If this is a
	 * threaded interrupt with ONESHOT set, we can end up with an
	 * interrupt storm.
	 */
	masked = irqd_irq_masked(idata);
	if (!masked)
		idata->chip->irq_mask(idata);
	irq_move_masked_irq(idata);
	if (!masked)
		idata->chip->irq_unmask(idata);
}