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
struct kvm_device_attr {int group; int /*<<< orphan*/  attr; } ;
struct kvm_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_DEV_VFIO_GROUP 130 
#define  KVM_DEV_VFIO_GROUP_ADD 129 
#define  KVM_DEV_VFIO_GROUP_DEL 128 

__attribute__((used)) static int kvm_vfio_has_attr(struct kvm_device *dev,
			     struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_VFIO_GROUP:
		switch (attr->attr) {
		case KVM_DEV_VFIO_GROUP_ADD:
		case KVM_DEV_VFIO_GROUP_DEL:
#ifdef CONFIG_SPAPR_TCE_IOMMU
		case KVM_DEV_VFIO_GROUP_SET_SPAPR_TCE:
#endif
			return 0;
		}

		break;
	}

	return -ENXIO;
}