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
typedef  int /*<<< orphan*/  vm_vaddr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ucall ;
struct ucall {int /*<<< orphan*/  cmd; } ;
struct kvm_vm {int dummy; } ;
struct TYPE_2__ {scalar_t__ port; } ;
struct kvm_run {scalar_t__ exit_reason; TYPE_1__ io; } ;
struct kvm_regs {scalar_t__ rdi; } ;

/* Variables and functions */
 scalar_t__ KVM_EXIT_IO ; 
 scalar_t__ UCALL_PIO_PORT ; 
 struct ucall* addr_gva2hva (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ucall*,struct ucall*,int) ; 
 int /*<<< orphan*/  vcpu_regs_get (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_regs*) ; 
 int /*<<< orphan*/  vcpu_run_complete_io (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 struct kvm_run* vcpu_state (struct kvm_vm*,int /*<<< orphan*/ ) ; 

uint64_t get_ucall(struct kvm_vm *vm, uint32_t vcpu_id, struct ucall *uc)
{
	struct kvm_run *run = vcpu_state(vm, vcpu_id);
	struct ucall ucall = {};

	if (run->exit_reason == KVM_EXIT_IO && run->io.port == UCALL_PIO_PORT) {
		struct kvm_regs regs;

		vcpu_regs_get(vm, vcpu_id, &regs);
		memcpy(&ucall, addr_gva2hva(vm, (vm_vaddr_t)regs.rdi),
		       sizeof(ucall));

		vcpu_run_complete_io(vm, vcpu_id);
		if (uc)
			memcpy(uc, &ucall, sizeof(ucall));
	}

	return ucall.cmd;
}