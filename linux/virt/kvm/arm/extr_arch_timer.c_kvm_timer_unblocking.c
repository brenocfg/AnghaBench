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
struct kvm_vcpu {int dummy; } ;
struct arch_timer_cpu {int /*<<< orphan*/  bg_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  soft_timer_cancel (int /*<<< orphan*/ *) ; 
 struct arch_timer_cpu* vcpu_timer (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_timer_unblocking(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = vcpu_timer(vcpu);

	soft_timer_cancel(&timer->bg_timer);
}