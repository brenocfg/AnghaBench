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
struct irq_data {struct irq_data* parent_data; } ;
struct irq_chip {int (* irq_set_vcpu_affinity ) (struct irq_data*,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 struct irq_desc* irq_get_desc_lock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_unlock (struct irq_desc*,unsigned long) ; 
 int stub1 (struct irq_data*,void*) ; 

int irq_set_vcpu_affinity(unsigned int irq, void *vcpu_info)
{
	unsigned long flags;
	struct irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);
	struct irq_data *data;
	struct irq_chip *chip;
	int ret = -ENOSYS;

	if (!desc)
		return -EINVAL;

	data = irq_desc_get_irq_data(desc);
	do {
		chip = irq_data_get_irq_chip(data);
		if (chip && chip->irq_set_vcpu_affinity)
			break;
#ifdef CONFIG_IRQ_DOMAIN_HIERARCHY
		data = data->parent_data;
#else
		data = NULL;
#endif
	} while (data);

	if (data)
		ret = chip->irq_set_vcpu_affinity(data, vcpu_info);
	irq_put_desc_unlock(desc, flags);

	return ret;
}