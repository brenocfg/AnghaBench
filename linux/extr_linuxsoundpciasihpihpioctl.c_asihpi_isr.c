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
struct hpi_adapter {int /*<<< orphan*/  (* interrupt_callback ) (struct hpi_adapter*) ;TYPE_1__* adapter; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int (* irq_query_and_clear ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  asihpi_irq_count ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hpi_adapter*) ; 

__attribute__((used)) static irqreturn_t asihpi_isr(int irq, void *dev_id)
{
	struct hpi_adapter *a = dev_id;
	int handled;

	if (!a->adapter->irq_query_and_clear) {
		pr_err("asihpi_isr ASI%04X:%d no handler\n", a->adapter->type,
			a->adapter->index);
		return IRQ_NONE;
	}

	handled = a->adapter->irq_query_and_clear(a->adapter, 0);

	if (!handled)
		return IRQ_NONE;

	asihpi_irq_count++;
	/* printk(KERN_INFO "asihpi_isr %d ASI%04X:%d irq handled\n",
	   asihpi_irq_count, a->adapter->type, a->adapter->index); */

	if (a->interrupt_callback)
		a->interrupt_callback(a);

	return IRQ_HANDLED;
}