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
struct TYPE_2__ {struct irq_chip* chip; } ;
struct irq_desc {TYPE_1__ irq_data; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct irq_desc* irq_get_desc_lock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_mark_irq (unsigned int) ; 
 int /*<<< orphan*/  irq_put_desc_unlock (struct irq_desc*,unsigned long) ; 
 struct irq_chip no_irq_chip ; 

int irq_set_chip(unsigned int irq, struct irq_chip *chip)
{
	unsigned long flags;
	struct irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	if (!desc)
		return -EINVAL;

	if (!chip)
		chip = &no_irq_chip;

	desc->irq_data.chip = chip;
	irq_put_desc_unlock(desc, flags);
	/*
	 * For !CONFIG_SPARSE_IRQ make the irq show up in
	 * allocated_irqs.
	 */
	irq_mark_irq(irq);
	return 0;
}