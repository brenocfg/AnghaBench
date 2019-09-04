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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 unsigned long PSCI_RET_SUCCESS ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned long kvm_psci_vcpu_suspend(struct kvm_vcpu *vcpu)
{
	/*
	 * NOTE: For simplicity, we make VCPU suspend emulation to be
	 * same-as WFI (Wait-for-interrupt) emulation.
	 *
	 * This means for KVM the wakeup events are interrupts and
	 * this is consistent with intended use of StateID as described
	 * in section 5.4.1 of PSCI v0.2 specification (ARM DEN 0022A).
	 *
	 * Further, we also treat power-down request to be same as
	 * stand-by request as-per section 5.4.2 clause 3 of PSCI v0.2
	 * specification (ARM DEN 0022A). This means all suspend states
	 * for KVM will preserve the register state.
	 */
	kvm_vcpu_block(vcpu);
	kvm_clear_request(KVM_REQ_UNHALT, vcpu);

	return PSCI_RET_SUCCESS;
}