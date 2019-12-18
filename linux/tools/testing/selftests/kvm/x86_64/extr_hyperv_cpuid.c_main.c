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
struct kvm_vm {int dummy; } ;
struct kvm_cpuid2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_CAP_HYPERV_CPUID ; 
 int /*<<< orphan*/  KVM_CAP_HYPERV_ENLIGHTENED_VMCS ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct kvm_cpuid2*) ; 
 int /*<<< orphan*/  guest_code ; 
 int kvm_check_cap (int /*<<< orphan*/ ) ; 
 struct kvm_cpuid2* kvm_get_supported_hv_cpuid (struct kvm_vm*) ; 
 int /*<<< orphan*/  kvm_vm_free (struct kvm_vm*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_hv_cpuid (struct kvm_cpuid2*,int) ; 
 int /*<<< orphan*/  test_hv_cpuid_e2big (struct kvm_vm*) ; 
 int /*<<< orphan*/  vcpu_enable_evmcs (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 struct kvm_vm* vm_create_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	struct kvm_vm *vm;
	int rv;
	struct kvm_cpuid2 *hv_cpuid_entries;

	/* Tell stdout not to buffer its content */
	setbuf(stdout, NULL);

	rv = kvm_check_cap(KVM_CAP_HYPERV_CPUID);
	if (!rv) {
		fprintf(stderr,
			"KVM_CAP_HYPERV_CPUID not supported, skip test\n");
		exit(KSFT_SKIP);
	}

	/* Create VM */
	vm = vm_create_default(VCPU_ID, 0, guest_code);

	test_hv_cpuid_e2big(vm);

	hv_cpuid_entries = kvm_get_supported_hv_cpuid(vm);
	if (!hv_cpuid_entries)
		return 1;

	test_hv_cpuid(hv_cpuid_entries, 0);

	free(hv_cpuid_entries);

	if (!kvm_check_cap(KVM_CAP_HYPERV_ENLIGHTENED_VMCS)) {
		fprintf(stderr,
			"Enlightened VMCS is unsupported, skip related test\n");
		goto vm_free;
	}

	vcpu_enable_evmcs(vm, VCPU_ID);

	hv_cpuid_entries = kvm_get_supported_hv_cpuid(vm);
	if (!hv_cpuid_entries)
		return 1;

	test_hv_cpuid(hv_cpuid_entries, 1);

	free(hv_cpuid_entries);

vm_free:
	kvm_vm_free(vm);

	return 0;
}