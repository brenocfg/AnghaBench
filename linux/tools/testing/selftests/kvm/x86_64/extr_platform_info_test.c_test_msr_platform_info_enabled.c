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
struct ucall {scalar_t__ cmd; int* args; } ;
struct kvm_vm {int dummy; } ;
struct kvm_run {scalar_t__ exit_reason; } ;

/* Variables and functions */
 scalar_t__ KVM_EXIT_IO ; 
 int MSR_PLATFORM_INFO_MAX_TURBO_RATIO ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 scalar_t__ UCALL_SYNC ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit_reason_str (scalar_t__) ; 
 int /*<<< orphan*/  get_ucall (struct kvm_vm*,int /*<<< orphan*/ ,struct ucall*) ; 
 int /*<<< orphan*/  set_msr_platform_info_enabled (struct kvm_vm*,int) ; 
 int ucall ; 
 int /*<<< orphan*/  vcpu_run (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 struct kvm_run* vcpu_state (struct kvm_vm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_msr_platform_info_enabled(struct kvm_vm *vm)
{
	struct kvm_run *run = vcpu_state(vm, VCPU_ID);
	struct ucall uc;

	set_msr_platform_info_enabled(vm, true);
	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->exit_reason == KVM_EXIT_IO,
			"Exit_reason other than KVM_EXIT_IO: %u (%s),\n",
			run->exit_reason,
			exit_reason_str(run->exit_reason));
	get_ucall(vm, VCPU_ID, &uc);
	TEST_ASSERT(uc.cmd == UCALL_SYNC,
			"Received ucall other than UCALL_SYNC: %u\n",
			ucall);
	TEST_ASSERT((uc.args[1] & MSR_PLATFORM_INFO_MAX_TURBO_RATIO) ==
		MSR_PLATFORM_INFO_MAX_TURBO_RATIO,
		"Expected MSR_PLATFORM_INFO to have max turbo ratio mask: %i.",
		MSR_PLATFORM_INFO_MAX_TURBO_RATIO);
}