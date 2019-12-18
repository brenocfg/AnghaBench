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
struct timer_map {struct arch_timer_context* direct_ptimer; struct arch_timer_context* direct_vtimer; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct arch_timer_context {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_percpu_irq (int) ; 
 int /*<<< orphan*/  get_timer_map (struct kvm_vcpu*,struct timer_map*) ; 
 int /*<<< orphan*/  has_gic_active_state ; 
 int host_vtimer_irq ; 
 scalar_t__ kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int,struct arch_timer_context*) ; 
 int /*<<< orphan*/  static_branch_unlikely (int /*<<< orphan*/ *) ; 
 scalar_t__ userspace_irqchip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t kvm_arch_timer_handler(int irq, void *dev_id)
{
	struct kvm_vcpu *vcpu = *(struct kvm_vcpu **)dev_id;
	struct arch_timer_context *ctx;
	struct timer_map map;

	/*
	 * We may see a timer interrupt after vcpu_put() has been called which
	 * sets the CPU's vcpu pointer to NULL, because even though the timer
	 * has been disabled in timer_save_state(), the hardware interrupt
	 * signal may not have been retired from the interrupt controller yet.
	 */
	if (!vcpu)
		return IRQ_HANDLED;

	get_timer_map(vcpu, &map);

	if (irq == host_vtimer_irq)
		ctx = map.direct_vtimer;
	else
		ctx = map.direct_ptimer;

	if (kvm_timer_should_fire(ctx))
		kvm_timer_update_irq(vcpu, true, ctx);

	if (userspace_irqchip(vcpu->kvm) &&
	    !static_branch_unlikely(&has_gic_active_state))
		disable_percpu_irq(host_vtimer_irq);

	return IRQ_HANDLED;
}