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
 int /*<<< orphan*/  KVM_SYSTEM_EVENT_RESET ; 
 int /*<<< orphan*/  kvm_prepare_system_event (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_psci_system_reset(struct kvm_vcpu *vcpu)
{
	kvm_prepare_system_event(vcpu, KVM_SYSTEM_EVENT_RESET);
}