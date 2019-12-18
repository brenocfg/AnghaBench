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
struct arch_timer_cpu {int /*<<< orphan*/  enabled; } ;
struct arch_timer_context {int loaded; int /*<<< orphan*/  cnt_ctl; int /*<<< orphan*/  cnt_cval; int /*<<< orphan*/  vcpu; } ;
typedef  enum kvm_arch_timers { ____Placeholder_kvm_arch_timers } kvm_arch_timers ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  NR_KVM_TIMERS 130 
 int /*<<< orphan*/  SYS_CNTP_CTL ; 
 int /*<<< orphan*/  SYS_CNTP_CVAL ; 
 int /*<<< orphan*/  SYS_CNTV_CTL ; 
 int /*<<< orphan*/  SYS_CNTV_CVAL ; 
#define  TIMER_PTIMER 129 
#define  TIMER_VTIMER 128 
 int arch_timer_ctx_index (struct arch_timer_context*) ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  trace_kvm_timer_restore_state (struct arch_timer_context*) ; 
 struct arch_timer_cpu* vcpu_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg_el0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_restore_state(struct arch_timer_context *ctx)
{
	struct arch_timer_cpu *timer = vcpu_timer(ctx->vcpu);
	enum kvm_arch_timers index = arch_timer_ctx_index(ctx);
	unsigned long flags;

	if (!timer->enabled)
		return;

	local_irq_save(flags);

	if (ctx->loaded)
		goto out;

	switch (index) {
	case TIMER_VTIMER:
		write_sysreg_el0(ctx->cnt_cval, SYS_CNTV_CVAL);
		isb();
		write_sysreg_el0(ctx->cnt_ctl, SYS_CNTV_CTL);
		break;
	case TIMER_PTIMER:
		write_sysreg_el0(ctx->cnt_cval, SYS_CNTP_CVAL);
		isb();
		write_sysreg_el0(ctx->cnt_ctl, SYS_CNTP_CTL);
		break;
	case NR_KVM_TIMERS:
		BUG();
	}

	trace_kvm_timer_restore_state(ctx);

	ctx->loaded = true;
out:
	local_irq_restore(flags);
}