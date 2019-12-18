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
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {int dummy; } ;
struct kvm_sregs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int /*<<< orphan*/ ) ; 
 int _vcpu_sregs_set (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_sregs*) ; 
 int /*<<< orphan*/  errno ; 

void vcpu_sregs_set(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_sregs *sregs)
{
	int ret = _vcpu_sregs_set(vm, vcpuid, sregs);
	TEST_ASSERT(ret == 0, "KVM_RUN IOCTL failed, "
		"rc: %i errno: %i", ret, errno);
}