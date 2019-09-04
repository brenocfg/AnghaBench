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
struct irq_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  free_irq (unsigned int,void*) ; 
 struct irq_info* irq_get_handler_data (unsigned int) ; 
 int /*<<< orphan*/  unbind_from_irq (unsigned int) ; 

void unbind_from_irqhandler(unsigned int irq, void *dev_id)
{
	struct irq_info *info = irq_get_handler_data(irq);

	if (WARN_ON(!info))
		return;
	free_irq(irq, dev_id);
	unbind_from_irq(irq);
}