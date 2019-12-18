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
struct ucall {int cmd; } ;
struct kvm_vm {int dummy; } ;
struct kvm_sregs {int /*<<< orphan*/  cr4; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; } ;
struct kvm_cpuid_entry2 {int ecx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_IO ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
#define  UCALL_ABORT 130 
#define  UCALL_DONE 129 
#define  UCALL_SYNC 128 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  X86_CR4_OSXSAVE ; 
 int X86_FEATURE_XSAVE ; 
 int _vcpu_run (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_reason_str (int /*<<< orphan*/ ) ; 
 int get_ucall (struct kvm_vm*,int /*<<< orphan*/ ,struct ucall*) ; 
 int /*<<< orphan*/  guest_code ; 
 int /*<<< orphan*/  kvm_get_supported_cpuid () ; 
 struct kvm_cpuid_entry2* kvm_get_supported_cpuid_entry (int) ; 
 int /*<<< orphan*/  kvm_vm_free (struct kvm_vm*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vcpu_set_cpuid (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_sregs_get (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_sregs*) ; 
 int /*<<< orphan*/  vcpu_sregs_set (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_sregs*) ; 
 struct kvm_run* vcpu_state (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 struct kvm_vm* vm_create_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	struct kvm_run *run;
	struct kvm_vm *vm;
	struct kvm_sregs sregs;
	struct kvm_cpuid_entry2 *entry;
	struct ucall uc;
	int rc;

	entry = kvm_get_supported_cpuid_entry(1);
	if (!(entry->ecx & X86_FEATURE_XSAVE)) {
		printf("XSAVE feature not supported, skipping test\n");
		return 0;
	}

	/* Tell stdout not to buffer its content */
	setbuf(stdout, NULL);

	/* Create VM */
	vm = vm_create_default(VCPU_ID, 0, guest_code);
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());
	run = vcpu_state(vm, VCPU_ID);

	while (1) {
		rc = _vcpu_run(vm, VCPU_ID);

		TEST_ASSERT(rc == 0, "vcpu_run failed: %d\n", rc);
		TEST_ASSERT(run->exit_reason == KVM_EXIT_IO,
			    "Unexpected exit reason: %u (%s),\n",
			    run->exit_reason,
			    exit_reason_str(run->exit_reason));

		switch (get_ucall(vm, VCPU_ID, &uc)) {
		case UCALL_SYNC:
			/* emulate hypervisor clearing CR4.OSXSAVE */
			vcpu_sregs_get(vm, VCPU_ID, &sregs);
			sregs.cr4 &= ~X86_CR4_OSXSAVE;
			vcpu_sregs_set(vm, VCPU_ID, &sregs);
			break;
		case UCALL_ABORT:
			TEST_ASSERT(false, "Guest CR4 bit (OSXSAVE) unsynchronized with CPUID bit.");
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