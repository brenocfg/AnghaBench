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
typedef  unsigned long u32 ;
struct vcpu_reset_state {int /*<<< orphan*/  reset; int /*<<< orphan*/  r0; int /*<<< orphan*/  be; int /*<<< orphan*/  pc; } ;
struct TYPE_2__ {int power_off; struct vcpu_reset_state reset_state; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ KVM_ARM_PSCI_0_1 ; 
 int /*<<< orphan*/  KVM_REQ_VCPU_RESET ; 
 unsigned long MPIDR_HWID_BITMASK ; 
 unsigned long PSCI_RET_ALREADY_ON ; 
 unsigned long PSCI_RET_INVALID_PARAMS ; 
 unsigned long PSCI_RET_SUCCESS ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 struct kvm_vcpu* kvm_mpidr_to_vcpu (struct kvm*,unsigned long) ; 
 scalar_t__ kvm_psci_version (struct kvm_vcpu*,struct kvm*) ; 
 int /*<<< orphan*/  kvm_vcpu_is_be (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_wake_up (struct kvm_vcpu*) ; 
 unsigned long smccc_get_arg1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smccc_get_arg2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smccc_get_arg3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ vcpu_mode_is_32bit (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned long kvm_psci_vcpu_on(struct kvm_vcpu *source_vcpu)
{
	struct vcpu_reset_state *reset_state;
	struct kvm *kvm = source_vcpu->kvm;
	struct kvm_vcpu *vcpu = NULL;
	unsigned long cpu_id;

	cpu_id = smccc_get_arg1(source_vcpu) & MPIDR_HWID_BITMASK;
	if (vcpu_mode_is_32bit(source_vcpu))
		cpu_id &= ~((u32) 0);

	vcpu = kvm_mpidr_to_vcpu(kvm, cpu_id);

	/*
	 * Make sure the caller requested a valid CPU and that the CPU is
	 * turned off.
	 */
	if (!vcpu)
		return PSCI_RET_INVALID_PARAMS;
	if (!vcpu->arch.power_off) {
		if (kvm_psci_version(source_vcpu, kvm) != KVM_ARM_PSCI_0_1)
			return PSCI_RET_ALREADY_ON;
		else
			return PSCI_RET_INVALID_PARAMS;
	}

	reset_state = &vcpu->arch.reset_state;

	reset_state->pc = smccc_get_arg2(source_vcpu);

	/* Propagate caller endianness */
	reset_state->be = kvm_vcpu_is_be(source_vcpu);

	/*
	 * NOTE: We always update r0 (or x0) because for PSCI v0.1
	 * the general puspose registers are undefined upon CPU_ON.
	 */
	reset_state->r0 = smccc_get_arg3(source_vcpu);

	WRITE_ONCE(reset_state->reset, true);
	kvm_make_request(KVM_REQ_VCPU_RESET, vcpu);

	/*
	 * Make sure the reset request is observed if the change to
	 * power_state is observed.
	 */
	smp_wmb();

	vcpu->arch.power_off = false;
	kvm_vcpu_wake_up(vcpu);

	return PSCI_RET_SUCCESS;
}