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
struct vgic_its {int /*<<< orphan*/  its_lock; } ;
struct kvm_msi {int /*<<< orphan*/  data; int /*<<< orphan*/  devid; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vgic_its*) ; 
 int PTR_ERR (struct vgic_its*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_its_inject_cached_translation (struct kvm*,struct kvm_msi*) ; 
 int vgic_its_trigger_msi (struct kvm*,struct vgic_its*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vgic_its* vgic_msi_to_its (struct kvm*,struct kvm_msi*) ; 

int vgic_its_inject_msi(struct kvm *kvm, struct kvm_msi *msi)
{
	struct vgic_its *its;
	int ret;

	if (!vgic_its_inject_cached_translation(kvm, msi))
		return 1;

	its = vgic_msi_to_its(kvm, msi);
	if (IS_ERR(its))
		return PTR_ERR(its);

	mutex_lock(&its->its_lock);
	ret = vgic_its_trigger_msi(kvm, its, msi->devid, msi->data);
	mutex_unlock(&its->its_lock);

	if (ret < 0)
		return ret;

	/*
	 * KVM_SIGNAL_MSI demands a return value > 0 for success and 0
	 * if the guest has blocked the MSI. So we map any LPI mapping
	 * related error to that.
	 */
	if (ret)
		return 0;
	else
		return 1;
}