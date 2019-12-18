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
struct preempt_notifier {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  ready; int /*<<< orphan*/  preempted; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_arch_sched_in (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_load (struct kvm_vcpu*,int) ; 
 struct kvm_vcpu* preempt_notifier_to_vcpu (struct preempt_notifier*) ; 

__attribute__((used)) static void kvm_sched_in(struct preempt_notifier *pn, int cpu)
{
	struct kvm_vcpu *vcpu = preempt_notifier_to_vcpu(pn);

	WRITE_ONCE(vcpu->preempted, false);
	WRITE_ONCE(vcpu->ready, false);

	kvm_arch_sched_in(vcpu, cpu);

	kvm_arch_vcpu_load(vcpu, cpu);
}