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

/* Variables and functions */
 int ENODEV ; 
#define  KVM_DEV_TYPE_ARM_VGIC_V2 129 
#define  KVM_DEV_TYPE_ARM_VGIC_V3 128 
 int /*<<< orphan*/  kvm_arm_vgic_v2_ops ; 
 int /*<<< orphan*/  kvm_arm_vgic_v3_ops ; 
 int kvm_register_device_ops (int /*<<< orphan*/ *,int const) ; 
 int kvm_vgic_register_its_device () ; 

int kvm_register_vgic_device(unsigned long type)
{
	int ret = -ENODEV;

	switch (type) {
	case KVM_DEV_TYPE_ARM_VGIC_V2:
		ret = kvm_register_device_ops(&kvm_arm_vgic_v2_ops,
					      KVM_DEV_TYPE_ARM_VGIC_V2);
		break;
	case KVM_DEV_TYPE_ARM_VGIC_V3:
		ret = kvm_register_device_ops(&kvm_arm_vgic_v3_ops,
					      KVM_DEV_TYPE_ARM_VGIC_V3);

		if (ret)
			break;
		ret = kvm_vgic_register_its_device();
		break;
	}

	return ret;
}