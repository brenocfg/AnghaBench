#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_device {TYPE_2__* ops; TYPE_1__* kvm; } ;
struct file {struct kvm_device* private_data; } ;
struct TYPE_6__ {scalar_t__ mm; } ;
struct TYPE_5__ {long (* ioctl ) (struct kvm_device*,unsigned int,unsigned long) ;int /*<<< orphan*/  has_attr; int /*<<< orphan*/  get_attr; int /*<<< orphan*/  set_attr; } ;
struct TYPE_4__ {scalar_t__ mm; } ;

/* Variables and functions */
 long EIO ; 
 long ENOTTY ; 
#define  KVM_GET_DEVICE_ATTR 130 
#define  KVM_HAS_DEVICE_ATTR 129 
#define  KVM_SET_DEVICE_ATTR 128 
 TYPE_3__* current ; 
 long kvm_device_ioctl_attr (struct kvm_device*,int /*<<< orphan*/ ,unsigned long) ; 
 long stub1 (struct kvm_device*,unsigned int,unsigned long) ; 

__attribute__((used)) static long kvm_device_ioctl(struct file *filp, unsigned int ioctl,
			     unsigned long arg)
{
	struct kvm_device *dev = filp->private_data;

	if (dev->kvm->mm != current->mm)
		return -EIO;

	switch (ioctl) {
	case KVM_SET_DEVICE_ATTR:
		return kvm_device_ioctl_attr(dev, dev->ops->set_attr, arg);
	case KVM_GET_DEVICE_ATTR:
		return kvm_device_ioctl_attr(dev, dev->ops->get_attr, arg);
	case KVM_HAS_DEVICE_ATTR:
		return kvm_device_ioctl_attr(dev, dev->ops->has_attr, arg);
	default:
		if (dev->ops->ioctl)
			return dev->ops->ioctl(dev, ioctl, arg);

		return -ENOTTY;
	}
}