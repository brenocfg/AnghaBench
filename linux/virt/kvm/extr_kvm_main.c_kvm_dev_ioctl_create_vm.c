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
struct kvm {int dummy; } ;
typedef  struct kvm file ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct kvm*) ; 
 int /*<<< orphan*/  KVM_EVENT_CREATE_VM ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PTR_ERR (struct kvm*) ; 
 struct kvm* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_install (int,struct kvm*) ; 
 int /*<<< orphan*/  fput (struct kvm*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int kvm_coalesced_mmio_init (struct kvm*) ; 
 struct kvm* kvm_create_vm (unsigned long) ; 
 scalar_t__ kvm_create_vm_debugfs (struct kvm*,int) ; 
 int /*<<< orphan*/  kvm_put_kvm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_uevent_notify_change (int /*<<< orphan*/ ,struct kvm*) ; 
 int /*<<< orphan*/  kvm_vm_fops ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 

__attribute__((used)) static int kvm_dev_ioctl_create_vm(unsigned long type)
{
	int r;
	struct kvm *kvm;
	struct file *file;

	kvm = kvm_create_vm(type);
	if (IS_ERR(kvm))
		return PTR_ERR(kvm);
#ifdef CONFIG_KVM_MMIO
	r = kvm_coalesced_mmio_init(kvm);
	if (r < 0)
		goto put_kvm;
#endif
	r = get_unused_fd_flags(O_CLOEXEC);
	if (r < 0)
		goto put_kvm;

	file = anon_inode_getfile("kvm-vm", &kvm_vm_fops, kvm, O_RDWR);
	if (IS_ERR(file)) {
		put_unused_fd(r);
		r = PTR_ERR(file);
		goto put_kvm;
	}

	/*
	 * Don't call kvm_put_kvm anymore at this point; file->f_op is
	 * already set, with ->release() being kvm_vm_release().  In error
	 * cases it will be called by the final fput(file) and will take
	 * care of doing kvm_put_kvm(kvm).
	 */
	if (kvm_create_vm_debugfs(kvm, r) < 0) {
		put_unused_fd(r);
		fput(file);
		return -ENOMEM;
	}
	kvm_uevent_notify_change(KVM_EVENT_CREATE_VM, kvm);

	fd_install(r, file);
	return r;

put_kvm:
	kvm_put_kvm(kvm);
	return r;
}