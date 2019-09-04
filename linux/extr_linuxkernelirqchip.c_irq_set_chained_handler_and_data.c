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
struct TYPE_2__ {void* handler_data; } ;
struct irq_desc {TYPE_1__ irq_common_data; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  __irq_do_set_handler (struct irq_desc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct irq_desc* irq_get_desc_buslock (unsigned int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_put_desc_busunlock (struct irq_desc*,unsigned long) ; 

void
irq_set_chained_handler_and_data(unsigned int irq, irq_flow_handler_t handle,
				 void *data)
{
	unsigned long flags;
	struct irq_desc *desc = irq_get_desc_buslock(irq, &flags, 0);

	if (!desc)
		return;

	desc->irq_common_data.handler_data = data;
	__irq_do_set_handler(desc, handle, 1, NULL);

	irq_put_desc_busunlock(desc, flags);
}