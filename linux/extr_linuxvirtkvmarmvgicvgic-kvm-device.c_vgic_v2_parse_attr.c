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
struct vgic_reg_attr {int addr; int /*<<< orphan*/  vcpu; } ;
struct kvm_device_attr {int attr; } ;
struct kvm_device {TYPE_1__* kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  online_vcpus; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_DEV_ARM_VGIC_CPUID_MASK ; 
 int KVM_DEV_ARM_VGIC_CPUID_SHIFT ; 
 int KVM_DEV_ARM_VGIC_OFFSET_MASK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_get_vcpu (TYPE_1__*,int) ; 

int vgic_v2_parse_attr(struct kvm_device *dev, struct kvm_device_attr *attr,
		       struct vgic_reg_attr *reg_attr)
{
	int cpuid;

	cpuid = (attr->attr & KVM_DEV_ARM_VGIC_CPUID_MASK) >>
		 KVM_DEV_ARM_VGIC_CPUID_SHIFT;

	if (cpuid >= atomic_read(&dev->kvm->online_vcpus))
		return -EINVAL;

	reg_attr->vcpu = kvm_get_vcpu(dev->kvm, cpuid);
	reg_attr->addr = attr->attr & KVM_DEV_ARM_VGIC_OFFSET_MASK;

	return 0;
}