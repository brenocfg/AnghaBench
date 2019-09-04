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
struct vcpu {struct kvm_run* state; } ;
struct kvm_vm {int dummy; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct vcpu* vcpu_find (struct kvm_vm*,int /*<<< orphan*/ ) ; 

struct kvm_run *vcpu_state(struct kvm_vm *vm, uint32_t vcpuid)
{
	struct vcpu *vcpu = vcpu_find(vm, vcpuid);
	TEST_ASSERT(vcpu != NULL, "vcpu not found, vcpuid: %u", vcpuid);

	return vcpu->state;
}