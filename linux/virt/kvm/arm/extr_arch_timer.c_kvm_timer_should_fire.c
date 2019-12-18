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
typedef  int u32 ;
struct arch_timer_context {scalar_t__ cnt_cval; scalar_t__ cntvoff; scalar_t__ loaded; } ;
typedef  enum kvm_arch_timers { ____Placeholder_kvm_arch_timers } kvm_arch_timers ;

/* Variables and functions */
 int ARCH_TIMER_CTRL_ENABLE ; 
 int ARCH_TIMER_CTRL_IT_MASK ; 
 int ARCH_TIMER_CTRL_IT_STAT ; 
#define  NR_KVM_TIMERS 130 
 int /*<<< orphan*/  SYS_CNTP_CTL ; 
 int /*<<< orphan*/  SYS_CNTV_CTL ; 
#define  TIMER_PTIMER 129 
#define  TIMER_VTIMER 128 
 int arch_timer_ctx_index (struct arch_timer_context*) ; 
 scalar_t__ kvm_phys_timer_read () ; 
 int /*<<< orphan*/  kvm_timer_irq_can_fire (struct arch_timer_context*) ; 
 int read_sysreg_el0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_timer_should_fire(struct arch_timer_context *timer_ctx)
{
	enum kvm_arch_timers index;
	u64 cval, now;

	if (!timer_ctx)
		return false;

	index = arch_timer_ctx_index(timer_ctx);

	if (timer_ctx->loaded) {
		u32 cnt_ctl = 0;

		switch (index) {
		case TIMER_VTIMER:
			cnt_ctl = read_sysreg_el0(SYS_CNTV_CTL);
			break;
		case TIMER_PTIMER:
			cnt_ctl = read_sysreg_el0(SYS_CNTP_CTL);
			break;
		case NR_KVM_TIMERS:
			/* GCC is braindead */
			cnt_ctl = 0;
			break;
		}

		return  (cnt_ctl & ARCH_TIMER_CTRL_ENABLE) &&
		        (cnt_ctl & ARCH_TIMER_CTRL_IT_STAT) &&
		       !(cnt_ctl & ARCH_TIMER_CTRL_IT_MASK);
	}

	if (!kvm_timer_irq_can_fire(timer_ctx))
		return false;

	cval = timer_ctx->cnt_cval;
	now = kvm_phys_timer_read() - timer_ctx->cntvoff;

	return cval <= now;
}