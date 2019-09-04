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
struct kvm_irq_routing_table {int** chip; } ;
struct kvm {int /*<<< orphan*/  irq_srcu; int /*<<< orphan*/  irq_routing; } ;

/* Variables and functions */
 struct kvm_irq_routing_table* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int kvm_irq_map_chip_pin(struct kvm *kvm, unsigned irqchip, unsigned pin)
{
	struct kvm_irq_routing_table *irq_rt;

	irq_rt = srcu_dereference(kvm->irq_routing, &kvm->irq_srcu);
	return irq_rt->chip[irqchip][pin];
}