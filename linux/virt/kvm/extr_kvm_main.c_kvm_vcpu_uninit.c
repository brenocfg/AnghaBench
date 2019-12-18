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
struct kvm_vcpu {scalar_t__ run; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

void kvm_vcpu_uninit(struct kvm_vcpu *vcpu)
{
	/*
	 * no need for rcu_read_lock as VCPU_RUN is the only place that
	 * will change the vcpu->pid pointer and on uninit all file
	 * descriptors are already gone.
	 */
	put_pid(rcu_dereference_protected(vcpu->pid, 1));
	kvm_arch_vcpu_uninit(vcpu);
	free_page((unsigned long)vcpu->run);
}