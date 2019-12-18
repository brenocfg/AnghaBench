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
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long KVM_ARM_PSCI_0_2 ; 
#define  PSCI_0_2_FN64_AFFINITY_INFO 138 
#define  PSCI_0_2_FN64_CPU_ON 137 
#define  PSCI_0_2_FN64_CPU_SUSPEND 136 
#define  PSCI_0_2_FN_AFFINITY_INFO 135 
#define  PSCI_0_2_FN_CPU_OFF 134 
#define  PSCI_0_2_FN_CPU_ON 133 
#define  PSCI_0_2_FN_CPU_SUSPEND 132 
#define  PSCI_0_2_FN_MIGRATE_INFO_TYPE 131 
#define  PSCI_0_2_FN_PSCI_VERSION 130 
#define  PSCI_0_2_FN_SYSTEM_OFF 129 
#define  PSCI_0_2_FN_SYSTEM_RESET 128 
 unsigned long PSCI_0_2_TOS_MP ; 
 unsigned long PSCI_RET_INTERNAL_FAILURE ; 
 unsigned long PSCI_RET_NOT_SUPPORTED ; 
 unsigned long PSCI_RET_SUCCESS ; 
 int /*<<< orphan*/  kvm_psci_system_off (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_psci_system_reset (struct kvm_vcpu*) ; 
 unsigned long kvm_psci_vcpu_affinity_info (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_psci_vcpu_off (struct kvm_vcpu*) ; 
 unsigned long kvm_psci_vcpu_on (struct kvm_vcpu*) ; 
 unsigned long kvm_psci_vcpu_suspend (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smccc_get_function (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smccc_set_retval (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_psci_0_2_call(struct kvm_vcpu *vcpu)
{
	struct kvm *kvm = vcpu->kvm;
	u32 psci_fn = smccc_get_function(vcpu);
	unsigned long val;
	int ret = 1;

	switch (psci_fn) {
	case PSCI_0_2_FN_PSCI_VERSION:
		/*
		 * Bits[31:16] = Major Version = 0
		 * Bits[15:0] = Minor Version = 2
		 */
		val = KVM_ARM_PSCI_0_2;
		break;
	case PSCI_0_2_FN_CPU_SUSPEND:
	case PSCI_0_2_FN64_CPU_SUSPEND:
		val = kvm_psci_vcpu_suspend(vcpu);
		break;
	case PSCI_0_2_FN_CPU_OFF:
		kvm_psci_vcpu_off(vcpu);
		val = PSCI_RET_SUCCESS;
		break;
	case PSCI_0_2_FN_CPU_ON:
	case PSCI_0_2_FN64_CPU_ON:
		mutex_lock(&kvm->lock);
		val = kvm_psci_vcpu_on(vcpu);
		mutex_unlock(&kvm->lock);
		break;
	case PSCI_0_2_FN_AFFINITY_INFO:
	case PSCI_0_2_FN64_AFFINITY_INFO:
		val = kvm_psci_vcpu_affinity_info(vcpu);
		break;
	case PSCI_0_2_FN_MIGRATE_INFO_TYPE:
		/*
		 * Trusted OS is MP hence does not require migration
	         * or
		 * Trusted OS is not present
		 */
		val = PSCI_0_2_TOS_MP;
		break;
	case PSCI_0_2_FN_SYSTEM_OFF:
		kvm_psci_system_off(vcpu);
		/*
		 * We should'nt be going back to guest VCPU after
		 * receiving SYSTEM_OFF request.
		 *
		 * If user space accidently/deliberately resumes
		 * guest VCPU after SYSTEM_OFF request then guest
		 * VCPU should see internal failure from PSCI return
		 * value. To achieve this, we preload r0 (or x0) with
		 * PSCI return value INTERNAL_FAILURE.
		 */
		val = PSCI_RET_INTERNAL_FAILURE;
		ret = 0;
		break;
	case PSCI_0_2_FN_SYSTEM_RESET:
		kvm_psci_system_reset(vcpu);
		/*
		 * Same reason as SYSTEM_OFF for preloading r0 (or x0)
		 * with PSCI return value INTERNAL_FAILURE.
		 */
		val = PSCI_RET_INTERNAL_FAILURE;
		ret = 0;
		break;
	default:
		val = PSCI_RET_NOT_SUPPORTED;
		break;
	}

	smccc_set_retval(vcpu, val, 0, 0, 0);
	return ret;
}