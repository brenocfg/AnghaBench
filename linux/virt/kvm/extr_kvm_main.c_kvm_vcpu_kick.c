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
struct kvm_vcpu {int cpu; } ;

/* Variables and functions */
 scalar_t__ cpu_online (int) ; 
 int get_cpu () ; 
 scalar_t__ kvm_arch_vcpu_should_kick (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_wake_up (struct kvm_vcpu*) ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_send_reschedule (int) ; 

void kvm_vcpu_kick(struct kvm_vcpu *vcpu)
{
	int me;
	int cpu = vcpu->cpu;

	if (kvm_vcpu_wake_up(vcpu))
		return;

	me = get_cpu();
	if (cpu != me && (unsigned)cpu < nr_cpu_ids && cpu_online(cpu))
		if (kvm_arch_vcpu_should_kick(vcpu))
			smp_send_reschedule(cpu);
	put_cpu();
}