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
struct irq_chip_generic {unsigned int irq_base; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  gc_lock ; 
 int /*<<< orphan*/  irq_modify_status (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_irq_chip ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

void irq_remove_generic_chip(struct irq_chip_generic *gc, u32 msk,
			     unsigned int clr, unsigned int set)
{
	unsigned int i = gc->irq_base;

	raw_spin_lock(&gc_lock);
	list_del(&gc->list);
	raw_spin_unlock(&gc_lock);

	for (; msk; msk >>= 1, i++) {
		if (!(msk & 0x01))
			continue;

		/* Remove handler first. That will mask the irq line */
		irq_set_handler(i, NULL);
		irq_set_chip(i, &no_irq_chip);
		irq_set_chip_data(i, NULL);
		irq_modify_status(i, clr, set);
	}
}