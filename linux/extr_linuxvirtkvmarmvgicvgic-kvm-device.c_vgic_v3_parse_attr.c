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
struct vgic_reg_attr {int addr; int /*<<< orphan*/  vcpu; } ;
struct kvm_device_attr {scalar_t__ group; unsigned long attr; } ;
struct kvm_device {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KVM_DEV_ARM_VGIC_GRP_DIST_REGS ; 
 int KVM_DEV_ARM_VGIC_OFFSET_MASK ; 
 unsigned long KVM_DEV_ARM_VGIC_V3_MPIDR_MASK ; 
 unsigned long KVM_DEV_ARM_VGIC_V3_MPIDR_SHIFT ; 
 unsigned long VGIC_TO_MPIDR (unsigned long) ; 
 int /*<<< orphan*/  kvm_get_vcpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mpidr_to_vcpu (int /*<<< orphan*/ ,unsigned long) ; 

int vgic_v3_parse_attr(struct kvm_device *dev, struct kvm_device_attr *attr,
		       struct vgic_reg_attr *reg_attr)
{
	unsigned long vgic_mpidr, mpidr_reg;

	/*
	 * For KVM_DEV_ARM_VGIC_GRP_DIST_REGS group,
	 * attr might not hold MPIDR. Hence assume vcpu0.
	 */
	if (attr->group != KVM_DEV_ARM_VGIC_GRP_DIST_REGS) {
		vgic_mpidr = (attr->attr & KVM_DEV_ARM_VGIC_V3_MPIDR_MASK) >>
			      KVM_DEV_ARM_VGIC_V3_MPIDR_SHIFT;

		mpidr_reg = VGIC_TO_MPIDR(vgic_mpidr);
		reg_attr->vcpu = kvm_mpidr_to_vcpu(dev->kvm, mpidr_reg);
	} else {
		reg_attr->vcpu = kvm_get_vcpu(dev->kvm, 0);
	}

	if (!reg_attr->vcpu)
		return -EINVAL;

	reg_attr->addr = attr->attr & KVM_DEV_ARM_VGIC_OFFSET_MASK;

	return 0;
}