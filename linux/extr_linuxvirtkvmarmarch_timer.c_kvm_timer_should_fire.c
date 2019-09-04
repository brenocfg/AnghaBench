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

/* Variables and functions */
 int ARCH_TIMER_CTRL_ENABLE ; 
 int ARCH_TIMER_CTRL_IT_MASK ; 
 int ARCH_TIMER_CTRL_IT_STAT ; 
 int /*<<< orphan*/  cntv_ctl ; 
 scalar_t__ kvm_phys_timer_read () ; 
 int /*<<< orphan*/  kvm_timer_irq_can_fire (struct arch_timer_context*) ; 
 int read_sysreg_el0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_timer_should_fire(struct arch_timer_context *timer_ctx)
{
	u64 cval, now;

	if (timer_ctx->loaded) {
		u32 cnt_ctl;

		/* Only the virtual timer can be loaded so far */
		cnt_ctl = read_sysreg_el0(cntv_ctl);
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