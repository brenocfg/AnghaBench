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
struct TYPE_2__ {void* chip_data; } ;
struct irq_desc {TYPE_1__ irq_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct irq_desc* irq_get_desc_lock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_unlock (struct irq_desc*,unsigned long) ; 

int irq_set_chip_data(unsigned int irq, void *data)
{
	unsigned long flags;
	struct irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	if (!desc)
		return -EINVAL;
	desc->irq_data.chip_data = data;
	irq_put_desc_unlock(desc, flags);
	return 0;
}