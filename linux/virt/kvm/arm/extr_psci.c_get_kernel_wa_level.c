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
typedef  int u64 ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_BP_HARDEN_NOT_REQUIRED 137 
#define  KVM_BP_HARDEN_UNKNOWN 136 
#define  KVM_BP_HARDEN_WA_NEEDED 135 
#define  KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1 134 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL ; 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL ; 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_REQUIRED ; 
#define  KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2 133 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_AVAIL ; 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL ; 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED ; 
 int KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_UNKNOWN ; 
#define  KVM_SSBD_FORCE_DISABLE 132 
#define  KVM_SSBD_FORCE_ENABLE 131 
#define  KVM_SSBD_KERNEL 130 
#define  KVM_SSBD_MITIGATED 129 
#define  KVM_SSBD_UNKNOWN 128 
 int /*<<< orphan*/  kvm_arm_harden_branch_predictor () ; 
 int /*<<< orphan*/  kvm_arm_have_ssbd () ; 

__attribute__((used)) static int get_kernel_wa_level(u64 regid)
{
	switch (regid) {
	case KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1:
		switch (kvm_arm_harden_branch_predictor()) {
		case KVM_BP_HARDEN_UNKNOWN:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL;
		case KVM_BP_HARDEN_WA_NEEDED:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL;
		case KVM_BP_HARDEN_NOT_REQUIRED:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_REQUIRED;
		}
		return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL;
	case KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2:
		switch (kvm_arm_have_ssbd()) {
		case KVM_SSBD_FORCE_DISABLE:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL;
		case KVM_SSBD_KERNEL:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_AVAIL;
		case KVM_SSBD_FORCE_ENABLE:
		case KVM_SSBD_MITIGATED:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED;
		case KVM_SSBD_UNKNOWN:
		default:
			return KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_UNKNOWN;
		}
	}

	return -EINVAL;
}