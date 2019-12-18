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
struct arch_timer_context {int dummy; } ;

/* Variables and functions */
#define  KVM_REG_ARM_PTIMER_CTL 132 
#define  KVM_REG_ARM_PTIMER_CVAL 131 
#define  KVM_REG_ARM_TIMER_CNT 130 
#define  KVM_REG_ARM_TIMER_CTL 129 
#define  KVM_REG_ARM_TIMER_CVAL 128 
 int /*<<< orphan*/  TIMER_REG_CTL ; 
 int /*<<< orphan*/  TIMER_REG_CVAL ; 
 int /*<<< orphan*/  kvm_arm_timer_write (struct kvm_vcpu*,struct arch_timer_context*,int /*<<< orphan*/ ,int) ; 
 int kvm_phys_timer_read () ; 
 int /*<<< orphan*/  update_vtimer_cntvoff (struct kvm_vcpu*,int) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

int kvm_arm_timer_set_reg(struct kvm_vcpu *vcpu, u64 regid, u64 value)
{
	struct arch_timer_context *timer;

	switch (regid) {
	case KVM_REG_ARM_TIMER_CTL:
		timer = vcpu_vtimer(vcpu);
		kvm_arm_timer_write(vcpu, timer, TIMER_REG_CTL, value);
		break;
	case KVM_REG_ARM_TIMER_CNT:
		timer = vcpu_vtimer(vcpu);
		update_vtimer_cntvoff(vcpu, kvm_phys_timer_read() - value);
		break;
	case KVM_REG_ARM_TIMER_CVAL:
		timer = vcpu_vtimer(vcpu);
		kvm_arm_timer_write(vcpu, timer, TIMER_REG_CVAL, value);
		break;
	case KVM_REG_ARM_PTIMER_CTL:
		timer = vcpu_ptimer(vcpu);
		kvm_arm_timer_write(vcpu, timer, TIMER_REG_CTL, value);
		break;
	case KVM_REG_ARM_PTIMER_CVAL:
		timer = vcpu_ptimer(vcpu);
		kvm_arm_timer_write(vcpu, timer, TIMER_REG_CVAL, value);
		break;

	default:
		return -1;
	}

	return 0;
}