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
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int level; int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int kvm_vgic_inject_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct arch_timer_context*) ; 
 int /*<<< orphan*/  trace_kvm_timer_update_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  userspace_irqchip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_timer_update_irq(struct kvm_vcpu *vcpu, bool new_level,
				 struct arch_timer_context *timer_ctx)
{
	int ret;

	timer_ctx->irq.level = new_level;
	trace_kvm_timer_update_irq(vcpu->vcpu_id, timer_ctx->irq.irq,
				   timer_ctx->irq.level);

	if (!userspace_irqchip(vcpu->kvm)) {
		ret = kvm_vgic_inject_irq(vcpu->kvm, vcpu->vcpu_id,
					  timer_ctx->irq.irq,
					  timer_ctx->irq.level,
					  timer_ctx);
		WARN_ON(ret);
	}
}