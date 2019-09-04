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
struct arch_timer_cpu {int /*<<< orphan*/  expired; int /*<<< orphan*/  bg_timer; } ;
struct TYPE_2__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtimer_restore_state (struct kvm_vcpu*) ; 

void kvm_timer_unschedule(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;

	vtimer_restore_state(vcpu);

	soft_timer_cancel(&timer->bg_timer, &timer->expired);
}