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
#define  KVM_PSCI_FN_CPU_OFF 129 
#define  KVM_PSCI_FN_CPU_ON 128 
 unsigned long PSCI_RET_NOT_SUPPORTED ; 
 unsigned long PSCI_RET_SUCCESS ; 
 int /*<<< orphan*/  kvm_psci_vcpu_off (struct kvm_vcpu*) ; 
 unsigned long kvm_psci_vcpu_on (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smccc_get_function (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smccc_set_retval (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_psci_0_1_call(struct kvm_vcpu *vcpu)
{
	struct kvm *kvm = vcpu->kvm;
	u32 psci_fn = smccc_get_function(vcpu);
	unsigned long val;

	switch (psci_fn) {
	case KVM_PSCI_FN_CPU_OFF:
		kvm_psci_vcpu_off(vcpu);
		val = PSCI_RET_SUCCESS;
		break;
	case KVM_PSCI_FN_CPU_ON:
		mutex_lock(&kvm->lock);
		val = kvm_psci_vcpu_on(vcpu);
		mutex_unlock(&kvm->lock);
		break;
	default:
		val = PSCI_RET_NOT_SUPPORTED;
		break;
	}

	smccc_set_retval(vcpu, val, 0, 0, 0);
	return 1;
}