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
 struct kvm_vcpu* kvm_arm_get_running_vcpu () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static struct kvm_vcpu *vgic_get_mmio_requester_vcpu(void)
{
	struct kvm_vcpu *vcpu;

	preempt_disable();
	vcpu = kvm_arm_get_running_vcpu();
	preempt_enable();
	return vcpu;
}