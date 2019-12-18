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
struct kvm_enable_cap {int cap; int* args; int /*<<< orphan*/  flags; } ;
struct kvm {int manual_dirty_log_protect; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 128 
 int kvm_vm_ioctl_enable_cap (struct kvm*,struct kvm_enable_cap*) ; 

__attribute__((used)) static int kvm_vm_ioctl_enable_cap_generic(struct kvm *kvm,
					   struct kvm_enable_cap *cap)
{
	switch (cap->cap) {
#ifdef CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT
	case KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2:
		if (cap->flags || (cap->args[0] & ~1))
			return -EINVAL;
		kvm->manual_dirty_log_protect = cap->args[0];
		return 0;
#endif
	default:
		return kvm_vm_ioctl_enable_cap(kvm, cap);
	}
}