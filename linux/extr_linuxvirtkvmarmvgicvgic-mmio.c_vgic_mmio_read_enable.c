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
typedef  unsigned int u32 ;
struct vgic_irq {scalar_t__ enabled; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 unsigned int VGIC_ADDR_TO_INTID (int /*<<< orphan*/ ,int) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

unsigned long vgic_mmio_read_enable(struct kvm_vcpu *vcpu,
				    gpa_t addr, unsigned int len)
{
	u32 intid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 value = 0;
	int i;

	/* Loop over all IRQs affected by this read */
	for (i = 0; i < len * 8; i++) {
		struct vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, intid + i);

		if (irq->enabled)
			value |= (1U << i);

		vgic_put_irq(vcpu->kvm, irq);
	}

	return value;
}