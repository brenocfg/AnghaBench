#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct arch_timer_cpu {scalar_t__ enabled; } ;
struct TYPE_4__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_1__ irq; scalar_t__ cnt_ctl; } ;

/* Variables and functions */
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_timer_update_state (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vgic_reset_mapped_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

int kvm_timer_vcpu_reset(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	/*
	 * The bits in CNTV_CTL are architecturally reset to UNKNOWN for ARMv8
	 * and to 0 for ARMv7.  We provide an implementation that always
	 * resets the timer to be disabled and unmasked and is compliant with
	 * the ARMv7 architecture.
	 */
	vtimer->cnt_ctl = 0;
	ptimer->cnt_ctl = 0;
	kvm_timer_update_state(vcpu);

	if (timer->enabled && irqchip_in_kernel(vcpu->kvm))
		kvm_vgic_reset_mapped_irq(vcpu, vtimer->irq.irq);

	return 0;
}