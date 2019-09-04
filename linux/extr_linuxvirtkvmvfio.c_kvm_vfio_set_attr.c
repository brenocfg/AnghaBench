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
struct kvm_device_attr {int group; int /*<<< orphan*/  addr; int /*<<< orphan*/  attr; } ;
struct kvm_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_DEV_VFIO_GROUP 128 
 int kvm_vfio_set_group (struct kvm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_vfio_set_attr(struct kvm_device *dev,
			     struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_VFIO_GROUP:
		return kvm_vfio_set_group(dev, attr->attr, attr->addr);
	}

	return -ENXIO;
}