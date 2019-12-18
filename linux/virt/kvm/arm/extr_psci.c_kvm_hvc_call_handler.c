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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
#define  ARM_SMCCC_ARCH_FEATURES_FUNC_ID 139 
#define  ARM_SMCCC_ARCH_WORKAROUND_1 138 
#define  ARM_SMCCC_ARCH_WORKAROUND_2 137 
 int ARM_SMCCC_VERSION_1_1 ; 
#define  ARM_SMCCC_VERSION_FUNC_ID 136 
#define  KVM_BP_HARDEN_NOT_REQUIRED 135 
#define  KVM_BP_HARDEN_UNKNOWN 134 
#define  KVM_BP_HARDEN_WA_NEEDED 133 
#define  KVM_SSBD_FORCE_DISABLE 132 
#define  KVM_SSBD_FORCE_ENABLE 131 
#define  KVM_SSBD_KERNEL 130 
#define  KVM_SSBD_MITIGATED 129 
#define  KVM_SSBD_UNKNOWN 128 
 int SMCCC_RET_NOT_REQUIRED ; 
 int SMCCC_RET_NOT_SUPPORTED ; 
 int SMCCC_RET_SUCCESS ; 
 int /*<<< orphan*/  kvm_arm_harden_branch_predictor () ; 
 int /*<<< orphan*/  kvm_arm_have_ssbd () ; 
 int kvm_psci_call (struct kvm_vcpu*) ; 
 int smccc_get_arg1 (struct kvm_vcpu*) ; 
 int smccc_get_function (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smccc_set_retval (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvm_hvc_call_handler(struct kvm_vcpu *vcpu)
{
	u32 func_id = smccc_get_function(vcpu);
	u32 val = SMCCC_RET_NOT_SUPPORTED;
	u32 feature;

	switch (func_id) {
	case ARM_SMCCC_VERSION_FUNC_ID:
		val = ARM_SMCCC_VERSION_1_1;
		break;
	case ARM_SMCCC_ARCH_FEATURES_FUNC_ID:
		feature = smccc_get_arg1(vcpu);
		switch(feature) {
		case ARM_SMCCC_ARCH_WORKAROUND_1:
			switch (kvm_arm_harden_branch_predictor()) {
			case KVM_BP_HARDEN_UNKNOWN:
				break;
			case KVM_BP_HARDEN_WA_NEEDED:
				val = SMCCC_RET_SUCCESS;
				break;
			case KVM_BP_HARDEN_NOT_REQUIRED:
				val = SMCCC_RET_NOT_REQUIRED;
				break;
			}
			break;
		case ARM_SMCCC_ARCH_WORKAROUND_2:
			switch (kvm_arm_have_ssbd()) {
			case KVM_SSBD_FORCE_DISABLE:
			case KVM_SSBD_UNKNOWN:
				break;
			case KVM_SSBD_KERNEL:
				val = SMCCC_RET_SUCCESS;
				break;
			case KVM_SSBD_FORCE_ENABLE:
			case KVM_SSBD_MITIGATED:
				val = SMCCC_RET_NOT_REQUIRED;
				break;
			}
			break;
		}
		break;
	default:
		return kvm_psci_call(vcpu);
	}

	smccc_set_retval(vcpu, val, 0, 0, 0);
	return 1;
}