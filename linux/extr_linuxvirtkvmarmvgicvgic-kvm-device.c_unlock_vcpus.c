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
struct kvm_vcpu {int /*<<< orphan*/  mutex; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_vcpus(struct kvm *kvm, int vcpu_lock_idx)
{
	struct kvm_vcpu *tmp_vcpu;

	for (; vcpu_lock_idx >= 0; vcpu_lock_idx--) {
		tmp_vcpu = kvm_get_vcpu(kvm, vcpu_lock_idx);
		mutex_unlock(&tmp_vcpu->mutex);
	}
}