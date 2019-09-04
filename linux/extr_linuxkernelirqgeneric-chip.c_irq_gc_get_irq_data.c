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
struct irq_data {int dummy; } ;
struct irq_chip_generic {unsigned int irq_base; int /*<<< orphan*/  installed; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 unsigned int __ffs (int /*<<< orphan*/ ) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 

__attribute__((used)) static struct irq_data *irq_gc_get_irq_data(struct irq_chip_generic *gc)
{
	unsigned int virq;

	if (!gc->domain)
		return irq_get_irq_data(gc->irq_base);

	/*
	 * We don't know which of the irqs has been actually
	 * installed. Use the first one.
	 */
	if (!gc->installed)
		return NULL;

	virq = irq_find_mapping(gc->domain, gc->irq_base + __ffs(gc->installed));
	return virq ? irq_get_irq_data(virq) : NULL;
}