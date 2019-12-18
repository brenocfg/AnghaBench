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
struct irq_data {int dummy; } ;
typedef  enum irqchip_irq_state { ____Placeholder_irqchip_irq_state } irqchip_irq_state ;

/* Variables and functions */
 int EINVAL ; 
 int __irq_get_irqchip_state (struct irq_data*,int,int*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 struct irq_desc* irq_get_desc_buslock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_busunlock (struct irq_desc*,unsigned long) ; 

int irq_get_irqchip_state(unsigned int irq, enum irqchip_irq_state which,
			  bool *state)
{
	struct irq_desc *desc;
	struct irq_data *data;
	unsigned long flags;
	int err = -EINVAL;

	desc = irq_get_desc_buslock(irq, &flags, 0);
	if (!desc)
		return err;

	data = irq_desc_get_irq_data(desc);

	err = __irq_get_irqchip_state(data, which, state);

	irq_put_desc_busunlock(desc, flags);
	return err;
}