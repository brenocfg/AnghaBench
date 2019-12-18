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
struct kvm_vcpu {int /*<<< orphan*/  preempt_notifier; } ;

/* Variables and functions */
 int get_cpu () ; 
 int /*<<< orphan*/  kvm_arch_vcpu_load (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  preempt_notifier_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cpu () ; 

void vcpu_load(struct kvm_vcpu *vcpu)
{
	int cpu = get_cpu();
	preempt_notifier_register(&vcpu->preempt_notifier);
	kvm_arch_vcpu_load(vcpu, cpu);
	put_cpu();
}