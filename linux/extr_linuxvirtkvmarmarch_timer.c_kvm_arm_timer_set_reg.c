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
struct arch_timer_context {int cnt_ctl; int cnt_cval; } ;

/* Variables and functions */
 int ARCH_TIMER_CTRL_IT_STAT ; 
#define  KVM_REG_ARM_PTIMER_CTL 132 
#define  KVM_REG_ARM_PTIMER_CVAL 131 
#define  KVM_REG_ARM_TIMER_CNT 130 
#define  KVM_REG_ARM_TIMER_CTL 129 
#define  KVM_REG_ARM_TIMER_CVAL 128 
 int kvm_phys_timer_read () ; 
 int /*<<< orphan*/  kvm_timer_update_state (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_vtimer_cntvoff (struct kvm_vcpu*,int) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

int kvm_arm_timer_set_reg(struct kvm_vcpu *vcpu, u64 regid, u64 value)
{
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	switch (regid) {
	case KVM_REG_ARM_TIMER_CTL:
		vtimer->cnt_ctl = value & ~ARCH_TIMER_CTRL_IT_STAT;
		break;
	case KVM_REG_ARM_TIMER_CNT:
		update_vtimer_cntvoff(vcpu, kvm_phys_timer_read() - value);
		break;
	case KVM_REG_ARM_TIMER_CVAL:
		vtimer->cnt_cval = value;
		break;
	case KVM_REG_ARM_PTIMER_CTL:
		ptimer->cnt_ctl = value & ~ARCH_TIMER_CTRL_IT_STAT;
		break;
	case KVM_REG_ARM_PTIMER_CVAL:
		ptimer->cnt_cval = value;
		break;

	default:
		return -1;
	}

	kvm_timer_update_state(vcpu);
	return 0;
}