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
struct kvm_nested_state {int flags; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_CAP_HYPERV_ENLIGHTENED_VMCS ; 
 int /*<<< orphan*/  KVM_CAP_NESTED_STATE ; 
 int KVM_STATE_NESTED_RUN_PENDING ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_evmcs ; 
 int /*<<< orphan*/  kvm_check_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vm_free (struct kvm_vm*) ; 
 int /*<<< orphan*/  nested_vmx_check_supported () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_default_state (struct kvm_nested_state*) ; 
 int /*<<< orphan*/  test_nested_state_expect_efault (struct kvm_vm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_nested_state_expect_einval (struct kvm_vm*,struct kvm_nested_state*) ; 
 int /*<<< orphan*/  test_vmx_nested_state (struct kvm_vm*) ; 
 struct kvm_vm* vm_create_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	struct kvm_vm *vm;
	struct kvm_nested_state state;

	have_evmcs = kvm_check_cap(KVM_CAP_HYPERV_ENLIGHTENED_VMCS);

	if (!kvm_check_cap(KVM_CAP_NESTED_STATE)) {
		printf("KVM_CAP_NESTED_STATE not available, skipping test\n");
		exit(KSFT_SKIP);
	}

	/*
	 * AMD currently does not implement set_nested_state, so for now we
	 * just early out.
	 */
	nested_vmx_check_supported();

	vm = vm_create_default(VCPU_ID, 0, 0);

	/* Passing a NULL kvm_nested_state causes a EFAULT. */
	test_nested_state_expect_efault(vm, NULL);

	/* 'size' cannot be smaller than sizeof(kvm_nested_state). */
	set_default_state(&state);
	state.size = 0;
	test_nested_state_expect_einval(vm, &state);

	/*
	 * Setting the flags 0xf fails the flags check.  The only flags that
	 * can be used are:
	 *     KVM_STATE_NESTED_GUEST_MODE
	 *     KVM_STATE_NESTED_RUN_PENDING
	 *     KVM_STATE_NESTED_EVMCS
	 */
	set_default_state(&state);
	state.flags = 0xf;
	test_nested_state_expect_einval(vm, &state);

	/*
	 * If KVM_STATE_NESTED_RUN_PENDING is set then
	 * KVM_STATE_NESTED_GUEST_MODE has to be set as well.
	 */
	set_default_state(&state);
	state.flags = KVM_STATE_NESTED_RUN_PENDING;
	test_nested_state_expect_einval(vm, &state);

	test_vmx_nested_state(vm);

	kvm_vm_free(vm);
	return 0;
}