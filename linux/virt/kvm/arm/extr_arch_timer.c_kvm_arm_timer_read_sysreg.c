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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
typedef  enum kvm_arch_timers { ____Placeholder_kvm_arch_timers } kvm_arch_timers ;
typedef  enum kvm_arch_timer_regs { ____Placeholder_kvm_arch_timer_regs } kvm_arch_timer_regs ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_arm_timer_read (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_timer_vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_timer_vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  vcpu_get_timer (struct kvm_vcpu*,int) ; 

u64 kvm_arm_timer_read_sysreg(struct kvm_vcpu *vcpu,
			      enum kvm_arch_timers tmr,
			      enum kvm_arch_timer_regs treg)
{
	u64 val;

	preempt_disable();
	kvm_timer_vcpu_put(vcpu);

	val = kvm_arm_timer_read(vcpu, vcpu_get_timer(vcpu, tmr), treg);

	kvm_timer_vcpu_load(vcpu);
	preempt_enable();

	return val;
}