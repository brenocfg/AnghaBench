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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
#define  KVM_REG_ARM_PTIMER_CNT 133 
#define  KVM_REG_ARM_PTIMER_CTL 132 
#define  KVM_REG_ARM_PTIMER_CVAL 131 
#define  KVM_REG_ARM_TIMER_CNT 130 
#define  KVM_REG_ARM_TIMER_CTL 129 
#define  KVM_REG_ARM_TIMER_CVAL 128 
 int /*<<< orphan*/  TIMER_REG_CNT ; 
 int /*<<< orphan*/  TIMER_REG_CTL ; 
 int /*<<< orphan*/  TIMER_REG_CVAL ; 
 int kvm_arm_timer_read (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_ptimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_vtimer (struct kvm_vcpu*) ; 

u64 kvm_arm_timer_get_reg(struct kvm_vcpu *vcpu, u64 regid)
{
	switch (regid) {
	case KVM_REG_ARM_TIMER_CTL:
		return kvm_arm_timer_read(vcpu,
					  vcpu_vtimer(vcpu), TIMER_REG_CTL);
	case KVM_REG_ARM_TIMER_CNT:
		return kvm_arm_timer_read(vcpu,
					  vcpu_vtimer(vcpu), TIMER_REG_CNT);
	case KVM_REG_ARM_TIMER_CVAL:
		return kvm_arm_timer_read(vcpu,
					  vcpu_vtimer(vcpu), TIMER_REG_CVAL);
	case KVM_REG_ARM_PTIMER_CTL:
		return kvm_arm_timer_read(vcpu,
					  vcpu_ptimer(vcpu), TIMER_REG_CTL);
	case KVM_REG_ARM_PTIMER_CNT:
		return kvm_arm_timer_read(vcpu,
					  vcpu_vtimer(vcpu), TIMER_REG_CNT);
	case KVM_REG_ARM_PTIMER_CVAL:
		return kvm_arm_timer_read(vcpu,
					  vcpu_ptimer(vcpu), TIMER_REG_CVAL);
	}
	return (u64)-1;
}