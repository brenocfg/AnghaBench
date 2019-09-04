#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vgic_its {int /*<<< orphan*/  its_lock; } ;
struct vgic_irq {int hw; int host_irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  devid; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ msi; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vgic_its*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int its_unmap_vlpi (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vgic_its* vgic_get_its (struct kvm*,struct kvm_kernel_irq_routing_entry*) ; 
 int vgic_its_resolve_lpi (struct kvm*,struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vgic_irq**) ; 
 int /*<<< orphan*/  vgic_supports_direct_msis (struct kvm*) ; 

int kvm_vgic_v4_unset_forwarding(struct kvm *kvm, int virq,
				 struct kvm_kernel_irq_routing_entry *irq_entry)
{
	struct vgic_its *its;
	struct vgic_irq *irq;
	int ret;

	if (!vgic_supports_direct_msis(kvm))
		return 0;

	/*
	 * Get the ITS, and escape early on error (not a valid
	 * doorbell for any of our vITSs).
	 */
	its = vgic_get_its(kvm, irq_entry);
	if (IS_ERR(its))
		return 0;

	mutex_lock(&its->its_lock);

	ret = vgic_its_resolve_lpi(kvm, its, irq_entry->msi.devid,
				   irq_entry->msi.data, &irq);
	if (ret)
		goto out;

	WARN_ON(!(irq->hw && irq->host_irq == virq));
	if (irq->hw) {
		irq->hw = false;
		ret = its_unmap_vlpi(virq);
	}

out:
	mutex_unlock(&its->its_lock);
	return ret;
}