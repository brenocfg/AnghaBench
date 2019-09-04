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
struct irq_data {int hwirq; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int GPIO_PER_REG ; 
 int /*<<< orphan*/  armada_37xx_irq_unmask (struct irq_data*) ; 

__attribute__((used)) static unsigned int armada_37xx_irq_startup(struct irq_data *d)
{
	/*
	 * The mask field is a "precomputed bitmask for accessing the
	 * chip registers" which was introduced for the generic
	 * irqchip framework. As we don't use this framework, we can
	 * reuse this field for our own usage.
	 */
	d->mask = BIT(d->hwirq % GPIO_PER_REG);

	armada_37xx_irq_unmask(d);

	return 0;
}