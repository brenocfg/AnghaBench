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
#define  KVM_DEV_ARM_VGIC_CTRL_INIT 135 
#define  KVM_DEV_ARM_VGIC_GRP_ADDR 134 
#define  KVM_DEV_ARM_VGIC_GRP_CPU_REGS 133 
#define  KVM_DEV_ARM_VGIC_GRP_CTRL 132 
#define  KVM_DEV_ARM_VGIC_GRP_DIST_REGS 131 
#define  KVM_DEV_ARM_VGIC_GRP_NR_IRQS 130 
#define  KVM_VGIC_V2_ADDR_TYPE_CPU 129 
#define  KVM_VGIC_V2_ADDR_TYPE_DIST 128 
 int vgic_v2_has_attr_regs (struct kvm_device*,struct kvm_device_attr*) ; 

__attribute__((used)) static int vgic_v2_has_attr(struct kvm_device *dev,
			    struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_ARM_VGIC_GRP_ADDR:
		switch (attr->attr) {
		case KVM_VGIC_V2_ADDR_TYPE_DIST:
		case KVM_VGIC_V2_ADDR_TYPE_CPU:
			return 0;
		}
		break;
	case KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	case KVM_DEV_ARM_VGIC_GRP_CPU_REGS:
		return vgic_v2_has_attr_regs(dev, attr);
	case KVM_DEV_ARM_VGIC_GRP_NR_IRQS:
		return 0;
	case KVM_DEV_ARM_VGIC_GRP_CTRL:
		switch (attr->attr) {
		case KVM_DEV_ARM_VGIC_CTRL_INIT:
			return 0;
		}
	}
	return -ENXIO;
}