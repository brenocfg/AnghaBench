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
struct TYPE_2__ {unsigned int pin; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ irqchip; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int VGIC_NR_PRIVATE_IRQS ; 
 int kvm_vgic_inject_irq (struct kvm*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_valid_spi (struct kvm*,unsigned int) ; 

__attribute__((used)) static int vgic_irqfd_set_irq(struct kvm_kernel_irq_routing_entry *e,
			struct kvm *kvm, int irq_source_id,
			int level, bool line_status)
{
	unsigned int spi_id = e->irqchip.pin + VGIC_NR_PRIVATE_IRQS;

	if (!vgic_valid_spi(kvm, spi_id))
		return -EINVAL;
	return kvm_vgic_inject_irq(kvm, 0, spi_id, level, NULL);
}