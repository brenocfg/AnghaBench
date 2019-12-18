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
struct vgic_irq {scalar_t__ config; int line_level; int pending_latch; int /*<<< orphan*/  irq_lock; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VGIC_CONFIG_LEVEL ; 
 unsigned int VGIC_NR_PRIVATE_IRQS ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_vgic_update_irq_pending (int,unsigned int,int) ; 
 struct vgic_irq* vgic_get_irq (struct kvm*,struct kvm_vcpu*,unsigned int) ; 
 int vgic_lazy_init (struct kvm*) ; 
 int /*<<< orphan*/  vgic_put_irq (struct kvm*,struct vgic_irq*) ; 
 int /*<<< orphan*/  vgic_queue_irq_unlock (struct kvm*,struct vgic_irq*,unsigned long) ; 
 int /*<<< orphan*/  vgic_validate_injection (struct vgic_irq*,int,void*) ; 

int kvm_vgic_inject_irq(struct kvm *kvm, int cpuid, unsigned int intid,
			bool level, void *owner)
{
	struct kvm_vcpu *vcpu;
	struct vgic_irq *irq;
	unsigned long flags;
	int ret;

	trace_vgic_update_irq_pending(cpuid, intid, level);

	ret = vgic_lazy_init(kvm);
	if (ret)
		return ret;

	vcpu = kvm_get_vcpu(kvm, cpuid);
	if (!vcpu && intid < VGIC_NR_PRIVATE_IRQS)
		return -EINVAL;

	irq = vgic_get_irq(kvm, vcpu, intid);
	if (!irq)
		return -EINVAL;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	if (!vgic_validate_injection(irq, level, owner)) {
		/* Nothing to see here, move along... */
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(kvm, irq);
		return 0;
	}

	if (irq->config == VGIC_CONFIG_LEVEL)
		irq->line_level = level;
	else
		irq->pending_latch = true;

	vgic_queue_irq_unlock(kvm, irq, flags);
	vgic_put_irq(kvm, irq);

	return 0;
}