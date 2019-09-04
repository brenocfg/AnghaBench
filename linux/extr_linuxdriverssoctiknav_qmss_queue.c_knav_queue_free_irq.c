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
struct knav_range_info {unsigned int queue_base; int flags; TYPE_1__* irqs; } ;
struct knav_queue_inst {unsigned int id; struct knav_range_info* range; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int RANGE_HAS_IRQ ; 
 int /*<<< orphan*/  free_irq (int,struct knav_queue_inst*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void knav_queue_free_irq(struct knav_queue_inst *inst)
{
	struct knav_range_info *range = inst->range;
	unsigned queue = inst->id - inst->range->queue_base;
	int irq;

	if (range->flags & RANGE_HAS_IRQ) {
		irq = range->irqs[queue].irq;
		irq_set_affinity_hint(irq, NULL);
		free_irq(irq, inst);
	}
}