#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vcpu {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int nmsrs; scalar_t__ size; TYPE_1__* entries; } ;
struct kvm_x86_state {TYPE_2__ nested; TYPE_2__ regs; TYPE_2__ debugregs; TYPE_2__ mp_state; TYPE_2__ events; TYPE_2__ msrs; TYPE_2__ sregs; TYPE_2__ xcrs; TYPE_2__ xsave; } ;
struct kvm_vm {int dummy; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_CAP_XCRS ; 
 int /*<<< orphan*/  KVM_SET_DEBUGREGS ; 
 int /*<<< orphan*/  KVM_SET_MP_STATE ; 
 int /*<<< orphan*/  KVM_SET_MSRS ; 
 int /*<<< orphan*/  KVM_SET_NESTED_STATE ; 
 int /*<<< orphan*/  KVM_SET_REGS ; 
 int /*<<< orphan*/  KVM_SET_SREGS ; 
 int /*<<< orphan*/  KVM_SET_VCPU_EVENTS ; 
 int /*<<< orphan*/  KVM_SET_XCRS ; 
 int /*<<< orphan*/  KVM_SET_XSAVE ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ kvm_check_cap (int /*<<< orphan*/ ) ; 
 struct vcpu* vcpu_find (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void vcpu_load_state(struct kvm_vm *vm, uint32_t vcpuid, struct kvm_x86_state *state)
{
	struct vcpu *vcpu = vcpu_find(vm, vcpuid);
	int r;

	r = ioctl(vcpu->fd, KVM_SET_XSAVE, &state->xsave);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_XSAVE, r: %i",
                r);

	if (kvm_check_cap(KVM_CAP_XCRS)) {
		r = ioctl(vcpu->fd, KVM_SET_XCRS, &state->xcrs);
		TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_XCRS, r: %i",
			    r);
	}

	r = ioctl(vcpu->fd, KVM_SET_SREGS, &state->sregs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_SREGS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_MSRS, &state->msrs);
        TEST_ASSERT(r == state->msrs.nmsrs, "Unexpected result from KVM_SET_MSRS, r: %i (failed at %x)",
                r, r == state->msrs.nmsrs ? -1 : state->msrs.entries[r].index);

	r = ioctl(vcpu->fd, KVM_SET_VCPU_EVENTS, &state->events);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_VCPU_EVENTS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_MP_STATE, &state->mp_state);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_MP_STATE, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_DEBUGREGS, &state->debugregs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_DEBUGREGS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_REGS, &state->regs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_REGS, r: %i",
                r);

	if (state->nested.size) {
		r = ioctl(vcpu->fd, KVM_SET_NESTED_STATE, &state->nested);
		TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_NESTED_STATE, r: %i",
			r);
	}
}