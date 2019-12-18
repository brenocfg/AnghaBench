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
struct kvm_device_ops {int (* create ) (struct kvm_device*,int) ;int /*<<< orphan*/  (* destroy ) (struct kvm_device*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* init ) (struct kvm_device*) ;} ;
struct kvm_device {int /*<<< orphan*/  vm_node; struct kvm* kvm; struct kvm_device_ops* ops; } ;
struct kvm_create_device {int flags; int fd; int /*<<< orphan*/  type; } ;
struct kvm {int /*<<< orphan*/  lock; int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct kvm_device_ops**) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int KVM_CREATE_DEVICE_TEST ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int anon_inode_getfd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kvm_device*,int) ; 
 int array_index_nospec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvm_device*) ; 
 int /*<<< orphan*/  kvm_device_fops ; 
 struct kvm_device_ops** kvm_device_ops_table ; 
 int /*<<< orphan*/  kvm_get_kvm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_put_kvm (struct kvm*) ; 
 struct kvm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct kvm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct kvm_device*) ; 
 int /*<<< orphan*/  stub3 (struct kvm_device*) ; 

__attribute__((used)) static int kvm_ioctl_create_device(struct kvm *kvm,
				   struct kvm_create_device *cd)
{
	struct kvm_device_ops *ops = NULL;
	struct kvm_device *dev;
	bool test = cd->flags & KVM_CREATE_DEVICE_TEST;
	int type;
	int ret;

	if (cd->type >= ARRAY_SIZE(kvm_device_ops_table))
		return -ENODEV;

	type = array_index_nospec(cd->type, ARRAY_SIZE(kvm_device_ops_table));
	ops = kvm_device_ops_table[type];
	if (ops == NULL)
		return -ENODEV;

	if (test)
		return 0;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL_ACCOUNT);
	if (!dev)
		return -ENOMEM;

	dev->ops = ops;
	dev->kvm = kvm;

	mutex_lock(&kvm->lock);
	ret = ops->create(dev, type);
	if (ret < 0) {
		mutex_unlock(&kvm->lock);
		kfree(dev);
		return ret;
	}
	list_add(&dev->vm_node, &kvm->devices);
	mutex_unlock(&kvm->lock);

	if (ops->init)
		ops->init(dev);

	kvm_get_kvm(kvm);
	ret = anon_inode_getfd(ops->name, &kvm_device_fops, dev, O_RDWR | O_CLOEXEC);
	if (ret < 0) {
		kvm_put_kvm(kvm);
		mutex_lock(&kvm->lock);
		list_del(&dev->vm_node);
		mutex_unlock(&kvm->lock);
		ops->destroy(dev);
		return ret;
	}

	cd->fd = ret;
	return 0;
}