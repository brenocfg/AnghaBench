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
struct vgic_irq {int /*<<< orphan*/  irq_lock; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  kvm_vgic_unmap_irq (struct vgic_irq*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  vgic_initialized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

int kvm_vgic_unmap_phys_irq(struct kvm_vcpu *vcpu, unsigned int vintid)
{
	struct vgic_irq *irq;
	unsigned long flags;

	if (!vgic_initialized(vcpu->kvm))
		return -EAGAIN;

	irq = vgic_get_irq(vcpu->kvm, vcpu, vintid);
	BUG_ON(!irq);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	kvm_vgic_unmap_irq(irq);
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);

	return 0;
}