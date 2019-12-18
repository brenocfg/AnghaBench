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
struct irq_sim {TYPE_1__* irqs; } ;
struct TYPE_2__ {int irqnum; } ;

/* Variables and functions */

int irq_sim_irqnum(struct irq_sim *sim, unsigned int offset)
{
	return sim->irqs[offset].irqnum;
}