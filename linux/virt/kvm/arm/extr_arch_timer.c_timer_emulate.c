#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int level; } ;
struct arch_timer_context {int /*<<< orphan*/  hrtimer; int /*<<< orphan*/  vcpu; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_timer_compute_delta (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_irq_can_fire (struct arch_timer_context*) ; 
 int kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (int /*<<< orphan*/ ,int,struct arch_timer_context*) ; 
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soft_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_timer_emulate (struct arch_timer_context*,int) ; 

__attribute__((used)) static void timer_emulate(struct arch_timer_context *ctx)
{
	bool should_fire = kvm_timer_should_fire(ctx);

	trace_kvm_timer_emulate(ctx, should_fire);

	if (should_fire != ctx->irq.level) {
		kvm_timer_update_irq(ctx->vcpu, should_fire, ctx);
		return;
	}

	/*
	 * If the timer can fire now, we don't need to have a soft timer
	 * scheduled for the future.  If the timer cannot fire at all,
	 * then we also don't need a soft timer.
	 */
	if (!kvm_timer_irq_can_fire(ctx)) {
		soft_timer_cancel(&ctx->hrtimer);
		return;
	}

	soft_timer_start(&ctx->hrtimer, kvm_timer_compute_delta(ctx));
}