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
struct task_struct {int dummy; } ;
struct preempt_notifier {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  ready; int /*<<< orphan*/  preempted; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kvm_arch_vcpu_put (struct kvm_vcpu*) ; 
 struct kvm_vcpu* preempt_notifier_to_vcpu (struct preempt_notifier*) ; 

__attribute__((used)) static void kvm_sched_out(struct preempt_notifier *pn,
			  struct task_struct *next)
{
	struct kvm_vcpu *vcpu = preempt_notifier_to_vcpu(pn);

	if (current->state == TASK_RUNNING) {
		WRITE_ONCE(vcpu->preempted, true);
		WRITE_ONCE(vcpu->ready, true);
	}
	kvm_arch_vcpu_put(vcpu);
}