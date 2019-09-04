#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
typedef  int u32 ;
struct vgic_irq {scalar_t__ config; scalar_t__ line_level; } ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct TYPE_5__ {int nr_spis; } ;
struct TYPE_6__ {TYPE_1__ vgic; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ VGIC_CONFIG_LEVEL ; 
 int VGIC_NR_PRIVATE_IRQS ; 
 int VGIC_NR_SGIS ; 
 struct vgic_irq* vgic_get_irq (TYPE_3__*,struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vgic_put_irq (TYPE_3__*,struct vgic_irq*) ; 

u64 vgic_read_irq_line_level_info(struct kvm_vcpu *vcpu, u32 intid)
{
	int i;
	u64 val = 0;
	int nr_irqs = vcpu->kvm->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS;

	for (i = 0; i < 32; i++) {
		struct vgic_irq *irq;

		if ((intid + i) < VGIC_NR_SGIS || (intid + i) >= nr_irqs)
			continue;

		irq = vgic_get_irq(vcpu->kvm, vcpu, intid + i);
		if (irq->config == VGIC_CONFIG_LEVEL && irq->line_level)
			val |= (1U << i);

		vgic_put_irq(vcpu->kvm, irq);
	}

	return val;
}