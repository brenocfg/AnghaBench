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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_ARM_PSCI_0_1 130 
#define  KVM_ARM_PSCI_0_2 129 
#define  KVM_ARM_PSCI_1_0 128 
 int kvm_psci_0_1_call (struct kvm_vcpu*) ; 
 int kvm_psci_0_2_call (struct kvm_vcpu*) ; 
 int kvm_psci_1_0_call (struct kvm_vcpu*) ; 
 int kvm_psci_version (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_psci_call(struct kvm_vcpu *vcpu)
{
	switch (kvm_psci_version(vcpu, vcpu->kvm)) {
	case KVM_ARM_PSCI_1_0:
		return kvm_psci_1_0_call(vcpu);
	case KVM_ARM_PSCI_0_2:
		return kvm_psci_0_2_call(vcpu);
	case KVM_ARM_PSCI_0_1:
		return kvm_psci_0_1_call(vcpu);
	default:
		return -EINVAL;
	};
}