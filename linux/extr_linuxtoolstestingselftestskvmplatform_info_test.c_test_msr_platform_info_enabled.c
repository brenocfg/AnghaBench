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
struct kvm_vm {int dummy; } ;
struct TYPE_2__ {int port; } ;
struct kvm_run {scalar_t__ exit_reason; TYPE_1__ io; } ;
struct guest_args {scalar_t__ port; int arg1; } ;

/* Variables and functions */
 scalar_t__ GUEST_PORT_SYNC ; 
 scalar_t__ KVM_EXIT_IO ; 
 int MSR_PLATFORM_INFO_MAX_TURBO_RATIO ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int /*<<< orphan*/  exit_reason_str (scalar_t__) ; 
 int /*<<< orphan*/  guest_args_read (struct kvm_vm*,int /*<<< orphan*/ ,struct guest_args*) ; 
 int /*<<< orphan*/  set_msr_platform_info_enabled (struct kvm_vm*,int) ; 
 int /*<<< orphan*/  vcpu_run (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 struct kvm_run* vcpu_state (struct kvm_vm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_msr_platform_info_enabled(struct kvm_vm *vm)
{
	struct kvm_run *run = vcpu_state(vm, VCPU_ID);
	struct guest_args args;

	set_msr_platform_info_enabled(vm, true);
	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->exit_reason == KVM_EXIT_IO,
			"Exit_reason other than KVM_EXIT_IO: %u (%s),\n",
			run->exit_reason,
			exit_reason_str(run->exit_reason));
	guest_args_read(vm, VCPU_ID, &args);
	TEST_ASSERT(args.port == GUEST_PORT_SYNC,
			"Received IO from port other than PORT_HOST_SYNC: %u\n",
			run->io.port);
	TEST_ASSERT((args.arg1 & MSR_PLATFORM_INFO_MAX_TURBO_RATIO) ==
		MSR_PLATFORM_INFO_MAX_TURBO_RATIO,
		"Expected MSR_PLATFORM_INFO to have max turbo ratio mask: %i.",
		MSR_PLATFORM_INFO_MAX_TURBO_RATIO);
}