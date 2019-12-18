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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct vgic_irq {int /*<<< orphan*/  host_irq; scalar_t__ hw; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  enabled; int /*<<< orphan*/  priority; struct kvm_vcpu* target_vcpu; scalar_t__ intid; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  propbaser; } ;
struct TYPE_4__ {TYPE_1__ vgic; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ GICR_PROPBASER_ADDRESS (int /*<<< orphan*/ ) ; 
 scalar_t__ GIC_LPI_OFFSET ; 
 int /*<<< orphan*/  LPI_PROP_ENABLE_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPI_PROP_PRIORITY (int /*<<< orphan*/ ) ; 
 int its_prop_update_vlpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int kvm_read_guest_lock (struct kvm*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vgic_queue_irq_unlock (struct kvm*,struct vgic_irq*,unsigned long) ; 

__attribute__((used)) static int update_lpi_config(struct kvm *kvm, struct vgic_irq *irq,
			     struct kvm_vcpu *filter_vcpu, bool needs_inv)
{
	u64 propbase = GICR_PROPBASER_ADDRESS(kvm->arch.vgic.propbaser);
	u8 prop;
	int ret;
	unsigned long flags;

	ret = kvm_read_guest_lock(kvm, propbase + irq->intid - GIC_LPI_OFFSET,
				  &prop, 1);

	if (ret)
		return ret;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	if (!filter_vcpu || filter_vcpu == irq->target_vcpu) {
		irq->priority = LPI_PROP_PRIORITY(prop);
		irq->enabled = LPI_PROP_ENABLE_BIT(prop);

		if (!irq->hw) {
			vgic_queue_irq_unlock(kvm, irq, flags);
			return 0;
		}
	}

	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	if (irq->hw)
		return its_prop_update_vlpi(irq->host_irq, prop, needs_inv);

	return 0;
}