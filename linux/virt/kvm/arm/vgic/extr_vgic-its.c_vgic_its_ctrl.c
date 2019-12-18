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
typedef  int u64 ;
struct vgic_its_abi {int (* save_tables ) (struct vgic_its*) ;int (* restore_tables ) (struct vgic_its*) ;} ;
struct vgic_its {int /*<<< orphan*/  its_lock; } ;
struct kvm {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
#define  KVM_DEV_ARM_ITS_CTRL_RESET 130 
#define  KVM_DEV_ARM_ITS_RESTORE_TABLES 129 
#define  KVM_DEV_ARM_ITS_SAVE_TABLES 128 
 int KVM_DEV_ARM_VGIC_CTRL_INIT ; 
 int /*<<< orphan*/  lock_all_vcpus (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct vgic_its*) ; 
 int stub2 (struct vgic_its*) ; 
 int /*<<< orphan*/  unlock_all_vcpus (struct kvm*) ; 
 struct vgic_its_abi* vgic_its_get_abi (struct vgic_its*) ; 
 int /*<<< orphan*/  vgic_its_reset (struct kvm*,struct vgic_its*) ; 

__attribute__((used)) static int vgic_its_ctrl(struct kvm *kvm, struct vgic_its *its, u64 attr)
{
	const struct vgic_its_abi *abi = vgic_its_get_abi(its);
	int ret = 0;

	if (attr == KVM_DEV_ARM_VGIC_CTRL_INIT) /* Nothing to do */
		return 0;

	mutex_lock(&kvm->lock);
	mutex_lock(&its->its_lock);

	if (!lock_all_vcpus(kvm)) {
		mutex_unlock(&its->its_lock);
		mutex_unlock(&kvm->lock);
		return -EBUSY;
	}

	switch (attr) {
	case KVM_DEV_ARM_ITS_CTRL_RESET:
		vgic_its_reset(kvm, its);
		break;
	case KVM_DEV_ARM_ITS_SAVE_TABLES:
		ret = abi->save_tables(its);
		break;
	case KVM_DEV_ARM_ITS_RESTORE_TABLES:
		ret = abi->restore_tables(its);
		break;
	}

	unlock_all_vcpus(kvm);
	mutex_unlock(&its->its_lock);
	mutex_unlock(&kvm->lock);
	return ret;
}