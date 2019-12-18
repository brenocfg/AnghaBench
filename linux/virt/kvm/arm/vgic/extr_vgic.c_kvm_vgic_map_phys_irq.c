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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_irq {int /*<<< orphan*/  irq_lock; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int kvm_vgic_map_irq (struct kvm_vcpu*,struct vgic_irq*,unsigned int,int (*) (int)) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

int kvm_vgic_map_phys_irq(struct kvm_vcpu *vcpu, unsigned int host_irq,
			  u32 vintid, bool (*get_input_level)(int vindid))
{
	struct vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, vintid);
	unsigned long flags;
	int ret;

	BUG_ON(!irq);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	ret = kvm_vgic_map_irq(vcpu, irq, host_irq, get_input_level);
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);

	return ret;
}