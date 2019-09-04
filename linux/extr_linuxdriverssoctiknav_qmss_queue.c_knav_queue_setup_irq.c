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
struct knav_range_info {unsigned int queue_base; int flags; TYPE_2__* kdev; TYPE_1__* irqs; } ;
struct knav_queue_inst {unsigned int id; int /*<<< orphan*/  irq_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int irq; int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 int RANGE_HAS_IRQ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int irq_set_affinity_hint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_queue_int_handler ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct knav_queue_inst*) ; 

__attribute__((used)) static int knav_queue_setup_irq(struct knav_range_info *range,
			  struct knav_queue_inst *inst)
{
	unsigned queue = inst->id - range->queue_base;
	int ret = 0, irq;

	if (range->flags & RANGE_HAS_IRQ) {
		irq = range->irqs[queue].irq;
		ret = request_irq(irq, knav_queue_int_handler, 0,
					inst->irq_name, inst);
		if (ret)
			return ret;
		disable_irq(irq);
		if (range->irqs[queue].cpu_mask) {
			ret = irq_set_affinity_hint(irq, range->irqs[queue].cpu_mask);
			if (ret) {
				dev_warn(range->kdev->dev,
					 "Failed to set IRQ affinity\n");
				return ret;
			}
		}
	}
	return ret;
}