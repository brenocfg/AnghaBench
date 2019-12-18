#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vgic_irq {struct kvm_vcpu* target_vcpu; scalar_t__ enabled; scalar_t__ vcpu; scalar_t__ active; int /*<<< orphan*/  irq_lock; } ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {TYPE_1__ vgic; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ irq_is_pending (struct vgic_irq*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kvm_vcpu *vgic_target_oracle(struct vgic_irq *irq)
{
	lockdep_assert_held(&irq->irq_lock);

	/* If the interrupt is active, it must stay on the current vcpu */
	if (irq->active)
		return irq->vcpu ? : irq->target_vcpu;

	/*
	 * If the IRQ is not active but enabled and pending, we should direct
	 * it to its configured target VCPU.
	 * If the distributor is disabled, pending interrupts shouldn't be
	 * forwarded.
	 */
	if (irq->enabled && irq_is_pending(irq)) {
		if (unlikely(irq->target_vcpu &&
			     !irq->target_vcpu->kvm->arch.vgic.enabled))
			return NULL;

		return irq->target_vcpu;
	}

	/* If neither active nor pending and enabled, then this IRQ should not
	 * be queued to any VCPU.
	 */
	return NULL;
}