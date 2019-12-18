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
typedef  int uint64_t ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_CAP_MSR_PLATFORM_INFO ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int MSR_PLATFORM_INFO_MAX_TURBO_RATIO ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  guest_code ; 
 int kvm_check_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vm_free (struct kvm_vm*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_msr_platform_info_disabled (struct kvm_vm*) ; 
 int /*<<< orphan*/  test_msr_platform_info_enabled (struct kvm_vm*) ; 
 int vcpu_get_msr (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_msr (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct kvm_vm* vm_create_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	struct kvm_vm *vm;
	int rv;
	uint64_t msr_platform_info;

	/* Tell stdout not to buffer its content */
	setbuf(stdout, NULL);

	rv = kvm_check_cap(KVM_CAP_MSR_PLATFORM_INFO);
	if (!rv) {
		fprintf(stderr,
			"KVM_CAP_MSR_PLATFORM_INFO not supported, skip test\n");
		exit(KSFT_SKIP);
	}

	vm = vm_create_default(VCPU_ID, 0, guest_code);

	msr_platform_info = vcpu_get_msr(vm, VCPU_ID, MSR_PLATFORM_INFO);
	vcpu_set_msr(vm, VCPU_ID, MSR_PLATFORM_INFO,
		msr_platform_info | MSR_PLATFORM_INFO_MAX_TURBO_RATIO);
	test_msr_platform_info_enabled(vm);
	test_msr_platform_info_disabled(vm);
	vcpu_set_msr(vm, VCPU_ID, MSR_PLATFORM_INFO, msr_platform_info);

	kvm_vm_free(vm);

	return 0;
}