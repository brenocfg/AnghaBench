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
typedef  scalar_t__ vm_vaddr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {int dummy; } ;
struct kvm_regs {int rflags; unsigned long rip; scalar_t__ rsp; } ;
struct kvm_mp_state {scalar_t__ mp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GUEST_STACK_VADDR_MIN ; 
 int DEFAULT_STACK_PGS ; 
 int getpagesize () ; 
 int /*<<< orphan*/  vcpu_regs_get (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_regs*) ; 
 int /*<<< orphan*/  vcpu_regs_set (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_regs*) ; 
 int /*<<< orphan*/  vcpu_set_mp_state (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_mp_state*) ; 
 int /*<<< orphan*/  vcpu_setup (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_vaddr_alloc (struct kvm_vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_vcpu_add (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void vm_vcpu_add_default(struct kvm_vm *vm, uint32_t vcpuid, void *guest_code)
{
	struct kvm_mp_state mp_state;
	struct kvm_regs regs;
	vm_vaddr_t stack_vaddr;
	stack_vaddr = vm_vaddr_alloc(vm, DEFAULT_STACK_PGS * getpagesize(),
				     DEFAULT_GUEST_STACK_VADDR_MIN, 0, 0);

	/* Create VCPU */
	vm_vcpu_add(vm, vcpuid);
	vcpu_setup(vm, vcpuid, 0, 0);

	/* Setup guest general purpose registers */
	vcpu_regs_get(vm, vcpuid, &regs);
	regs.rflags = regs.rflags | 0x2;
	regs.rsp = stack_vaddr + (DEFAULT_STACK_PGS * getpagesize());
	regs.rip = (unsigned long) guest_code;
	vcpu_regs_set(vm, vcpuid, &regs);

	/* Setup the MP state */
	mp_state.mp_state = 0;
	vcpu_set_mp_state(vm, vcpuid, &mp_state);
}