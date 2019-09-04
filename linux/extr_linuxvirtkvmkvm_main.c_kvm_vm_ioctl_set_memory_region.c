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
typedef  scalar_t__ u16 ;
struct kvm_userspace_memory_region {scalar_t__ slot; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KVM_USER_MEM_SLOTS ; 
 int kvm_set_memory_region (struct kvm*,struct kvm_userspace_memory_region*) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_memory_region(struct kvm *kvm,
					  struct kvm_userspace_memory_region *mem)
{
	if ((u16)mem->slot >= KVM_USER_MEM_SLOTS)
		return -EINVAL;

	return kvm_set_memory_region(kvm, mem);
}