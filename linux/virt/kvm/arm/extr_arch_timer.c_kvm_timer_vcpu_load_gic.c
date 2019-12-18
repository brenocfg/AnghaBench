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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int level; int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_1__ irq; struct kvm_vcpu* vcpu; } ;

/* Variables and functions */
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_timer_should_fire (struct arch_timer_context*) ; 
 int /*<<< orphan*/  kvm_timer_update_irq (struct kvm_vcpu*,int /*<<< orphan*/ ,struct arch_timer_context*) ; 
 int kvm_vgic_map_is_active (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_timer_irq_phys_active (struct arch_timer_context*,int) ; 

__attribute__((used)) static void kvm_timer_vcpu_load_gic(struct arch_timer_context *ctx)
{
	struct kvm_vcpu *vcpu = ctx->vcpu;
	bool phys_active = false;

	/*
	 * Update the timer output so that it is likely to match the
	 * state we're about to restore. If the timer expires between
	 * this point and the register restoration, we'll take the
	 * interrupt anyway.
	 */
	kvm_timer_update_irq(ctx->vcpu, kvm_timer_should_fire(ctx), ctx);

	if (irqchip_in_kernel(vcpu->kvm))
		phys_active = kvm_vgic_map_is_active(vcpu, ctx->irq.irq);

	phys_active |= ctx->irq.level;

	set_timer_irq_phys_active(ctx, phys_active);
}