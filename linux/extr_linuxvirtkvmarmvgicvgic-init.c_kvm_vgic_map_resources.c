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
struct vgic_dist {scalar_t__ vgic_model; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V2 ; 
 int /*<<< orphan*/  __kvm_vgic_destroy (struct kvm*) ; 
 int /*<<< orphan*/  irqchip_in_kernel (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vgic_v2_map_resources (struct kvm*) ; 
 int vgic_v3_map_resources (struct kvm*) ; 

int kvm_vgic_map_resources(struct kvm *kvm)
{
	struct vgic_dist *dist = &kvm->arch.vgic;
	int ret = 0;

	mutex_lock(&kvm->lock);
	if (!irqchip_in_kernel(kvm))
		goto out;

	if (dist->vgic_model == KVM_DEV_TYPE_ARM_VGIC_V2)
		ret = vgic_v2_map_resources(kvm);
	else
		ret = vgic_v3_map_resources(kvm);

	if (ret)
		__kvm_vgic_destroy(kvm);

out:
	mutex_unlock(&kvm->lock);
	return ret;
}