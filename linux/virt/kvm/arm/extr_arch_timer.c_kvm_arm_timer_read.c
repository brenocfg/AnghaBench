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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;
struct arch_timer_context {scalar_t__ cntvoff; scalar_t__ cnt_cval; } ;
typedef  enum kvm_arch_timer_regs { ____Placeholder_kvm_arch_timer_regs } kvm_arch_timer_regs ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  TIMER_REG_CNT 131 
#define  TIMER_REG_CTL 130 
#define  TIMER_REG_CVAL 129 
#define  TIMER_REG_TVAL 128 
 scalar_t__ kvm_phys_timer_read () ; 
 scalar_t__ read_timer_ctl (struct arch_timer_context*) ; 

__attribute__((used)) static u64 kvm_arm_timer_read(struct kvm_vcpu *vcpu,
			      struct arch_timer_context *timer,
			      enum kvm_arch_timer_regs treg)
{
	u64 val;

	switch (treg) {
	case TIMER_REG_TVAL:
		val = timer->cnt_cval - kvm_phys_timer_read() + timer->cntvoff;
		break;

	case TIMER_REG_CTL:
		val = read_timer_ctl(timer);
		break;

	case TIMER_REG_CVAL:
		val = timer->cnt_cval;
		break;

	case TIMER_REG_CNT:
		val = kvm_phys_timer_read() - timer->cntvoff;
		break;

	default:
		BUG();
	}

	return val;
}