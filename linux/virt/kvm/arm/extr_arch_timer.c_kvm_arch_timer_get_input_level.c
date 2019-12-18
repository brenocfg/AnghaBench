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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int irq; } ;
struct arch_timer_context {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct kvm_vcpu* kvm_arm_get_running_vcpu () ; 
 int kvm_timer_should_fire (struct arch_timer_context*) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

bool kvm_arch_timer_get_input_level(int vintid)
{
	struct kvm_vcpu *vcpu = kvm_arm_get_running_vcpu();
	struct arch_timer_context *timer;

	if (vintid == vcpu_vtimer(vcpu)->irq.irq)
		timer = vcpu_vtimer(vcpu);
	else if (vintid == vcpu_ptimer(vcpu)->irq.irq)
		timer = vcpu_ptimer(vcpu);
	else
		BUG();

	return kvm_timer_should_fire(timer);
}