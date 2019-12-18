#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgic_irq {int /*<<< orphan*/  irq_lock; struct kvm_vcpu* vcpu; int /*<<< orphan*/  ap_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  ap_list_lock; int /*<<< orphan*/  ap_list_head; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_IRQ_PENDING ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_get_irq_kref (struct vgic_irq*) ; 
 struct kvm_vcpu* vgic_target_oracle (struct vgic_irq*) ; 

bool vgic_queue_irq_unlock(struct kvm *kvm, struct vgic_irq *irq,
			   unsigned long flags)
{
	struct kvm_vcpu *vcpu;

	lockdep_assert_held(&irq->irq_lock);

retry:
	vcpu = vgic_target_oracle(irq);
	if (irq->vcpu || !vcpu) {
		/*
		 * If this IRQ is already on a VCPU's ap_list, then it
		 * cannot be moved or modified and there is no more work for
		 * us to do.
		 *
		 * Otherwise, if the irq is not pending and enabled, it does
		 * not need to be inserted into an ap_list and there is also
		 * no more work for us to do.
		 */
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		/*
		 * We have to kick the VCPU here, because we could be
		 * queueing an edge-triggered interrupt for which we
		 * get no EOI maintenance interrupt. In that case,
		 * while the IRQ is already on the VCPU's AP list, the
		 * VCPU could have EOI'ed the original interrupt and
		 * won't see this one until it exits for some other
		 * reason.
		 */
		if (vcpu) {
			kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
			kvm_vcpu_kick(vcpu);
		}
		return false;
	}

	/*
	 * We must unlock the irq lock to take the ap_list_lock where
	 * we are going to insert this new pending interrupt.
	 */
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	/* someone can do stuff here, which we re-check below */

	raw_spin_lock_irqsave(&vcpu->arch.vgic_cpu.ap_list_lock, flags);
	raw_spin_lock(&irq->irq_lock);

	/*
	 * Did something change behind our backs?
	 *
	 * There are two cases:
	 * 1) The irq lost its pending state or was disabled behind our
	 *    backs and/or it was queued to another VCPU's ap_list.
	 * 2) Someone changed the affinity on this irq behind our
	 *    backs and we are now holding the wrong ap_list_lock.
	 *
	 * In both cases, drop the locks and retry.
	 */

	if (unlikely(irq->vcpu || vcpu != vgic_target_oracle(irq))) {
		raw_spin_unlock(&irq->irq_lock);
		raw_spin_unlock_irqrestore(&vcpu->arch.vgic_cpu.ap_list_lock,
					   flags);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		goto retry;
	}

	/*
	 * Grab a reference to the irq to reflect the fact that it is
	 * now in the ap_list.
	 */
	vgic_get_irq_kref(irq);
	list_add_tail(&irq->ap_list, &vcpu->arch.vgic_cpu.ap_list_head);
	irq->vcpu = vcpu;

	raw_spin_unlock(&irq->irq_lock);
	raw_spin_unlock_irqrestore(&vcpu->arch.vgic_cpu.ap_list_lock, flags);

	kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
	kvm_vcpu_kick(vcpu);

	return true;
}