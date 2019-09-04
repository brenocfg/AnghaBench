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
typedef  int u32 ;
struct irq_data {int mask; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_calc_mask ) (struct irq_data*) ;} ;
struct irq_chip_type {int /*<<< orphan*/  handler; struct irq_chip chip; } ;
struct irq_chip_generic {unsigned int irq_base; unsigned int irq_cnt; int /*<<< orphan*/  list; struct irq_chip_type* chip_types; } ;
typedef  enum irq_gc_flags { ____Placeholder_irq_gc_flags } irq_gc_flags ;

/* Variables and functions */
 int IRQ_GC_INIT_NESTED_LOCK ; 
 int IRQ_GC_NO_MASK ; 
 int /*<<< orphan*/  gc_list ; 
 int /*<<< orphan*/  gc_lock ; 
 int /*<<< orphan*/  irq_gc_init_mask_cache (struct irq_chip_generic*,int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_modify_status (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irq_nested_lock_class ; 
 int /*<<< orphan*/  irq_nested_request_class ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_set_lockdep_class (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

void irq_setup_generic_chip(struct irq_chip_generic *gc, u32 msk,
			    enum irq_gc_flags flags, unsigned int clr,
			    unsigned int set)
{
	struct irq_chip_type *ct = gc->chip_types;
	struct irq_chip *chip = &ct->chip;
	unsigned int i;

	raw_spin_lock(&gc_lock);
	list_add_tail(&gc->list, &gc_list);
	raw_spin_unlock(&gc_lock);

	irq_gc_init_mask_cache(gc, flags);

	for (i = gc->irq_base; msk; msk >>= 1, i++) {
		if (!(msk & 0x01))
			continue;

		if (flags & IRQ_GC_INIT_NESTED_LOCK)
			irq_set_lockdep_class(i, &irq_nested_lock_class,
					      &irq_nested_request_class);

		if (!(flags & IRQ_GC_NO_MASK)) {
			struct irq_data *d = irq_get_irq_data(i);

			if (chip->irq_calc_mask)
				chip->irq_calc_mask(d);
			else
				d->mask = 1 << (i - gc->irq_base);
		}
		irq_set_chip_and_handler(i, chip, ct->handler);
		irq_set_chip_data(i, gc);
		irq_modify_status(i, clr, set);
	}
	gc->irq_cnt = i - gc->irq_base;
}