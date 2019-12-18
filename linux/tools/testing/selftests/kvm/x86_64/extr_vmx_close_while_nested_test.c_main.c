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
struct ucall {char const* cmd; scalar_t__* args; } ;
struct TYPE_2__ {scalar_t__ port; } ;
struct kvm_run {scalar_t__ exit_reason; TYPE_1__ io; } ;

/* Variables and functions */
 scalar_t__ KVM_EXIT_IO ; 
 scalar_t__ PORT_L0_EXIT ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,char const*,...) ; 
#define  UCALL_ABORT 128 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit_reason_str (scalar_t__) ; 
 int get_ucall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucall*) ; 
 int /*<<< orphan*/  kvm_get_supported_cpuid () ; 
 scalar_t__ l1_guest_code ; 
 int /*<<< orphan*/  nested_vmx_check_supported () ; 
 int /*<<< orphan*/  vcpu_alloc_vmx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_args_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_run* vcpu_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm ; 
 int /*<<< orphan*/  vm_create_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int main(int argc, char *argv[])
{
	vm_vaddr_t vmx_pages_gva;

	nested_vmx_check_supported();

	vm = vm_create_default(VCPU_ID, 0, (void *) l1_guest_code);
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());

	/* Allocate VMX pages and shared descriptors (vmx_pages). */
	vcpu_alloc_vmx(vm, &vmx_pages_gva);
	vcpu_args_set(vm, VCPU_ID, 1, vmx_pages_gva);

	for (;;) {
		volatile struct kvm_run *run = vcpu_state(vm, VCPU_ID);
		struct ucall uc;

		vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->exit_reason == KVM_EXIT_IO,
			    "Got exit_reason other than KVM_EXIT_IO: %u (%s)\n",
			    run->exit_reason,
			    exit_reason_str(run->exit_reason));

		if (run->io.port == PORT_L0_EXIT)
			break;

		switch (get_ucall(vm, VCPU_ID, &uc)) {
		case UCALL_ABORT:
			TEST_ASSERT(false, "%s", (const char *)uc.args[0]);
			/* NOT REACHED */
		default:
			TEST_ASSERT(false, "Unknown ucall 0x%x.", uc.cmd);
		}
	}
}