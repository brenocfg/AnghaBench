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
typedef  int /*<<< orphan*/  vm_vaddr_t ;
struct ucall {char const* cmd; scalar_t__* args; } ;
struct kvm_run {scalar_t__ exit_reason; } ;

/* Variables and functions */
 scalar_t__ KVM_EXIT_IO ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,char const*,...) ; 
#define  UCALL_ABORT 130 
#define  UCALL_DONE 129 
#define  UCALL_SYNC 128 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit_reason_str (scalar_t__) ; 
 int get_ucall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucall*) ; 
 int /*<<< orphan*/  kvm_get_supported_cpuid () ; 
 int /*<<< orphan*/  kvm_vm_free (int /*<<< orphan*/ ) ; 
 scalar_t__ l1_guest_code ; 
 int /*<<< orphan*/  nested_vmx_check_supported () ; 
 int /*<<< orphan*/  report (scalar_t__) ; 
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

		switch (get_ucall(vm, VCPU_ID, &uc)) {
		case UCALL_ABORT:
			TEST_ASSERT(false, "%s", (const char *)uc.args[0]);
			/* NOT REACHED */
		case UCALL_SYNC:
			report(uc.args[1]);
			break;
		case UCALL_DONE:
			goto done;
		default:
			TEST_ASSERT(false, "Unknown ucall 0x%x.", uc.cmd);
		}
	}

	kvm_vm_free(vm);
done:
	return 0;
}