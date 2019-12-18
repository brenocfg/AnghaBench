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
struct vm_area_struct {int dummy; } ;
struct kvm_device {TYPE_1__* ops; } ;
struct file {struct kvm_device* private_data; } ;
struct TYPE_2__ {int (* mmap ) (struct kvm_device*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct kvm_device*,struct vm_area_struct*) ; 

__attribute__((used)) static int kvm_device_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct kvm_device *dev = filp->private_data;

	if (dev->ops->mmap)
		return dev->ops->mmap(dev, vma);

	return -ENODEV;
}