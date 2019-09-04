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
struct kvm_vcpu {TYPE_2__* run; } ;
struct kvm_sync_regs {int device_irq_level; } ;
struct arch_timer_context {int dummy; } ;
struct TYPE_3__ {struct kvm_sync_regs regs; } ;
struct TYPE_4__ {TYPE_1__ s; } ;

/* Variables and functions */
 int KVM_ARM_DEV_EL1_PTIMER ; 
 int KVM_ARM_DEV_EL1_VTIMER ; 
 scalar_t__ kvm_timer_should_fire (struct arch_timer_context*) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

void kvm_timer_update_run(struct kvm_vcpu *vcpu)
{
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);
	struct kvm_sync_regs *regs = &vcpu->run->s.regs;

	/* Populate the device bitmap with the timer states */
	regs->device_irq_level &= ~(KVM_ARM_DEV_EL1_VTIMER |
				    KVM_ARM_DEV_EL1_PTIMER);
	if (kvm_timer_should_fire(vtimer))
		regs->device_irq_level |= KVM_ARM_DEV_EL1_VTIMER;
	if (kvm_timer_should_fire(ptimer))
		regs->device_irq_level |= KVM_ARM_DEV_EL1_PTIMER;
}