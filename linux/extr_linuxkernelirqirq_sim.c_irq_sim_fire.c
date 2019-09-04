#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  work; int /*<<< orphan*/  irq; } ;
struct irq_sim {TYPE_2__ work_ctx; TYPE_1__* irqs; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_sim_irqnum (struct irq_sim*,unsigned int) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 

void irq_sim_fire(struct irq_sim *sim, unsigned int offset)
{
	if (sim->irqs[offset].enabled) {
		sim->work_ctx.irq = irq_sim_irqnum(sim, offset);
		irq_work_queue(&sim->work_ctx.work);
	}
}