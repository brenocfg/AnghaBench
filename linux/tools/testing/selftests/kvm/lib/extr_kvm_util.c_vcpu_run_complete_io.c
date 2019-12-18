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
typedef  int /*<<< orphan*/  uint32_t ;
struct vcpu {TYPE_1__* state; int /*<<< orphan*/  fd; } ;
struct kvm_vm {int dummy; } ;
struct TYPE_2__ {int immediate_exit; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  KVM_RUN ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 scalar_t__ errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vcpu* vcpu_find (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void vcpu_run_complete_io(struct kvm_vm *vm, uint32_t vcpuid)
{
	struct vcpu *vcpu = vcpu_find(vm, vcpuid);
	int ret;

	TEST_ASSERT(vcpu != NULL, "vcpu not found, vcpuid: %u", vcpuid);

	vcpu->state->immediate_exit = 1;
	ret = ioctl(vcpu->fd, KVM_RUN, NULL);
	vcpu->state->immediate_exit = 0;

	TEST_ASSERT(ret == -1 && errno == EINTR,
		    "KVM_RUN IOCTL didn't exit immediately, rc: %i, errno: %i",
		    ret, errno);
}