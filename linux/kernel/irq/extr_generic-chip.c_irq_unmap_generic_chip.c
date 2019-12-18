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
struct irq_domain_chip_generic {unsigned int irqs_per_chip; } ;
struct irq_domain {struct irq_domain_chip_generic* gc; } ;
struct irq_data {unsigned int hwirq; } ;
struct irq_chip_generic {int /*<<< orphan*/  installed; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  no_irq_chip ; 

__attribute__((used)) static void irq_unmap_generic_chip(struct irq_domain *d, unsigned int virq)
{
	struct irq_data *data = irq_domain_get_irq_data(d, virq);
	struct irq_domain_chip_generic *dgc = d->gc;
	unsigned int hw_irq = data->hwirq;
	struct irq_chip_generic *gc;
	int irq_idx;

	gc = irq_get_domain_generic_chip(d, hw_irq);
	if (!gc)
		return;

	irq_idx = hw_irq % dgc->irqs_per_chip;

	clear_bit(irq_idx, &gc->installed);
	irq_domain_set_info(d, virq, hw_irq, &no_irq_chip, NULL, NULL, NULL,
			    NULL);

}