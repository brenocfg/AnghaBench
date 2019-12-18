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
struct vgic_irq {void* owner; int /*<<< orphan*/  irq_lock; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  irq_is_ppi (unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vgic_irq* vgic_get_irq (int /*<<< orphan*/ ,struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  vgic_initialized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_valid_spi (int /*<<< orphan*/ ,unsigned int) ; 

int kvm_vgic_set_owner(struct kvm_vcpu *vcpu, unsigned int intid, void *owner)
{
	struct vgic_irq *irq;
	unsigned long flags;
	int ret = 0;

	if (!vgic_initialized(vcpu->kvm))
		return -EAGAIN;

	/* SGIs and LPIs cannot be wired up to any device */
	if (!irq_is_ppi(intid) && !vgic_valid_spi(vcpu->kvm, intid))
		return -EINVAL;

	irq = vgic_get_irq(vcpu->kvm, vcpu, intid);
	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	if (irq->owner && irq->owner != owner)
		ret = -EEXIST;
	else
		irq->owner = owner;
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	return ret;
}