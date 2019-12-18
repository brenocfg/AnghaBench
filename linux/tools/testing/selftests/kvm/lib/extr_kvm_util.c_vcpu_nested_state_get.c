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
struct vcpu {int /*<<< orphan*/  fd; } ;
struct kvm_vm {int dummy; } ;
struct kvm_nested_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_GET_NESTED_STATE ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_nested_state*) ; 
 struct vcpu* vcpu_find (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void vcpu_nested_state_get(struct kvm_vm *vm, uint32_t vcpuid,
			   struct kvm_nested_state *state)
{
	struct vcpu *vcpu = vcpu_find(vm, vcpuid);
	int ret;

	TEST_ASSERT(vcpu != NULL, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_GET_NESTED_STATE, state);
	TEST_ASSERT(ret == 0,
		"KVM_SET_NESTED_STATE failed, ret: %i errno: %i",
		ret, errno);
}