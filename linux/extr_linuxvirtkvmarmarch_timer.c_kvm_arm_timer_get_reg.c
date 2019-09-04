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
struct arch_timer_context {int cntvoff; int cnt_cval; } ;

/* Variables and functions */
#define  KVM_REG_ARM_PTIMER_CNT 133 
#define  KVM_REG_ARM_PTIMER_CTL 132 
#define  KVM_REG_ARM_PTIMER_CVAL 131 
#define  KVM_REG_ARM_TIMER_CNT 130 
#define  KVM_REG_ARM_TIMER_CTL 129 
#define  KVM_REG_ARM_TIMER_CVAL 128 
 int kvm_phys_timer_read () ; 
 int read_timer_ctl (struct arch_timer_context*) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

u64 kvm_arm_timer_get_reg(struct kvm_vcpu *vcpu, u64 regid)
{
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);

	switch (regid) {
	case KVM_REG_ARM_TIMER_CTL:
		return read_timer_ctl(vtimer);
	case KVM_REG_ARM_TIMER_CNT:
		return kvm_phys_timer_read() - vtimer->cntvoff;
	case KVM_REG_ARM_TIMER_CVAL:
		return vtimer->cnt_cval;
	case KVM_REG_ARM_PTIMER_CTL:
		return read_timer_ctl(ptimer);
	case KVM_REG_ARM_PTIMER_CVAL:
		return ptimer->cnt_cval;
	case KVM_REG_ARM_PTIMER_CNT:
		return kvm_phys_timer_read();
	}
	return (u64)-1;
}