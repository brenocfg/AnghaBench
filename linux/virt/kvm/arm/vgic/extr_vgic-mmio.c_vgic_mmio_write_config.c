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
typedef  scalar_t__ u32 ;
struct vgic_irq {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  config; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 scalar_t__ VGIC_ADDR_TO_INTID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGIC_CONFIG_EDGE ; 
 int /*<<< orphan*/  VGIC_CONFIG_LEVEL ; 
 scalar_t__ VGIC_NR_PRIVATE_IRQS ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

void vgic_mmio_write_config(struct kvm_vcpu *vcpu,
			    gpa_t addr, unsigned int len,
			    unsigned long val)
{
	u32 intid = VGIC_ADDR_TO_INTID(addr, 2);
	int i;
	unsigned long flags;

	for (i = 0; i < len * 4; i++) {
		struct vgic_irq *irq;

		/*
		 * The configuration cannot be changed for SGIs in general,
		 * for PPIs this is IMPLEMENTATION DEFINED. The arch timer
		 * code relies on PPIs being level triggered, so we also
		 * make them read-only here.
		 */
		if (intid + i < VGIC_NR_PRIVATE_IRQS)
			continue;

		irq = vgic_get_irq(vcpu->kvm, vcpu, intid + i);
		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		if (test_bit(i * 2 + 1, &val))
			irq->config = VGIC_CONFIG_EDGE;
		else
			irq->config = VGIC_CONFIG_LEVEL;

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	}
}