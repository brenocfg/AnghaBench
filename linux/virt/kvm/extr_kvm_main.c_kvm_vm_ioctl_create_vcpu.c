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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int /*<<< orphan*/  debugfs_dentry; int /*<<< orphan*/  preempt_notifier; } ;
struct kvm {scalar_t__ created_vcpus; int /*<<< orphan*/  lock; int /*<<< orphan*/  online_vcpus; struct kvm_vcpu** vcpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct kvm_vcpu*) ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct kvm_vcpu*) ; 
 scalar_t__ KVM_MAX_VCPUS ; 
 int /*<<< orphan*/  KVM_MAX_VCPU_ID ; 
 int PTR_ERR (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int create_vcpu_fd (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* kvm_arch_vcpu_create (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_destroy (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_postcreate (struct kvm_vcpu*) ; 
 int kvm_arch_vcpu_setup (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_create_vcpu_debugfs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_get_kvm (struct kvm*) ; 
 scalar_t__ kvm_get_vcpu_by_id (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_preempt_ops ; 
 int /*<<< orphan*/  kvm_put_kvm (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_notifier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int kvm_vm_ioctl_create_vcpu(struct kvm *kvm, u32 id)
{
	int r;
	struct kvm_vcpu *vcpu;

	if (id >= KVM_MAX_VCPU_ID)
		return -EINVAL;

	mutex_lock(&kvm->lock);
	if (kvm->created_vcpus == KVM_MAX_VCPUS) {
		mutex_unlock(&kvm->lock);
		return -EINVAL;
	}

	kvm->created_vcpus++;
	mutex_unlock(&kvm->lock);

	vcpu = kvm_arch_vcpu_create(kvm, id);
	if (IS_ERR(vcpu)) {
		r = PTR_ERR(vcpu);
		goto vcpu_decrement;
	}

	preempt_notifier_init(&vcpu->preempt_notifier, &kvm_preempt_ops);

	r = kvm_arch_vcpu_setup(vcpu);
	if (r)
		goto vcpu_destroy;

	kvm_create_vcpu_debugfs(vcpu);

	mutex_lock(&kvm->lock);
	if (kvm_get_vcpu_by_id(kvm, id)) {
		r = -EEXIST;
		goto unlock_vcpu_destroy;
	}

	BUG_ON(kvm->vcpus[atomic_read(&kvm->online_vcpus)]);

	/* Now it's all set up, let userspace reach it */
	kvm_get_kvm(kvm);
	r = create_vcpu_fd(vcpu);
	if (r < 0) {
		kvm_put_kvm(kvm);
		goto unlock_vcpu_destroy;
	}

	kvm->vcpus[atomic_read(&kvm->online_vcpus)] = vcpu;

	/*
	 * Pairs with smp_rmb() in kvm_get_vcpu.  Write kvm->vcpus
	 * before kvm->online_vcpu's incremented value.
	 */
	smp_wmb();
	atomic_inc(&kvm->online_vcpus);

	mutex_unlock(&kvm->lock);
	kvm_arch_vcpu_postcreate(vcpu);
	return r;

unlock_vcpu_destroy:
	mutex_unlock(&kvm->lock);
	debugfs_remove_recursive(vcpu->debugfs_dentry);
vcpu_destroy:
	kvm_arch_vcpu_destroy(vcpu);
vcpu_decrement:
	mutex_lock(&kvm->lock);
	kvm->created_vcpus--;
	mutex_unlock(&kvm->lock);
	return r;
}