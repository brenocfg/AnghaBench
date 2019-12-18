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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct arch_timer_cpu {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmask_vtimer_irq_user (struct kvm_vcpu*) ; 
 struct arch_timer_cpu* vcpu_timer (struct kvm_vcpu*) ; 

void kvm_timer_sync_hwstate(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = vcpu_timer(vcpu);

	if (unlikely(!timer->enabled))
		return;

	if (unlikely(!irqchip_in_kernel(vcpu->kvm)))
		unmask_vtimer_irq_user(vcpu);
}