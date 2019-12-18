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
struct vgic_irq {int /*<<< orphan*/  irq_lock; scalar_t__ active; scalar_t__ hw; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  vgic_initialized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_put_irq (int /*<<< orphan*/ ,struct vgic_irq*) ; 

bool kvm_vgic_map_is_active(struct kvm_vcpu *vcpu, unsigned int vintid)
{
	struct vgic_irq *irq;
	bool map_is_active;
	unsigned long flags;

	if (!vgic_initialized(vcpu->kvm))
		return false;

	irq = vgic_get_irq(vcpu->kvm, vcpu, vintid);
	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	map_is_active = irq->hw && irq->active;
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);

	return map_is_active;
}