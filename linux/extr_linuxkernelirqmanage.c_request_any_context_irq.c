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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int IRQC_IS_HARDIRQ ; 
 int IRQC_IS_NESTED ; 
 unsigned int IRQ_NOTCONNECTED ; 
 scalar_t__ irq_settings_is_nested_thread (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 
 int request_threaded_irq (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 

int request_any_context_irq(unsigned int irq, irq_handler_t handler,
			    unsigned long flags, const char *name, void *dev_id)
{
	struct irq_desc *desc;
	int ret;

	if (irq == IRQ_NOTCONNECTED)
		return -ENOTCONN;

	desc = irq_to_desc(irq);
	if (!desc)
		return -EINVAL;

	if (irq_settings_is_nested_thread(desc)) {
		ret = request_threaded_irq(irq, NULL, handler,
					   flags, name, dev_id);
		return !ret ? IRQC_IS_NESTED : ret;
	}

	ret = request_irq(irq, handler, flags, name, dev_id);
	return !ret ? IRQC_IS_HARDIRQ : ret;
}