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
 int /*<<< orphan*/  KVM_DEV_TYPE_ARM_VGIC_ITS ; 
 int /*<<< orphan*/  kvm_arm_vgic_its_ops ; 
 int kvm_register_device_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int kvm_vgic_register_its_device(void)
{
	return kvm_register_device_ops(&kvm_arm_vgic_its_ops,
				       KVM_DEV_TYPE_ARM_VGIC_ITS);
}