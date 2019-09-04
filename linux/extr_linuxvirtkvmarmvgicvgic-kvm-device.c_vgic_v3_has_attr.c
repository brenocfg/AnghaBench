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
struct kvm_device_attr {int group; int attr; } ;
struct kvm_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_DEV_ARM_VGIC_CTRL_INIT 139 
#define  KVM_DEV_ARM_VGIC_GRP_ADDR 138 
#define  KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS 137 
#define  KVM_DEV_ARM_VGIC_GRP_CTRL 136 
#define  KVM_DEV_ARM_VGIC_GRP_DIST_REGS 135 
#define  KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO 134 
#define  KVM_DEV_ARM_VGIC_GRP_NR_IRQS 133 
#define  KVM_DEV_ARM_VGIC_GRP_REDIST_REGS 132 
 int KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK ; 
 int KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT ; 
#define  KVM_DEV_ARM_VGIC_SAVE_PENDING_TABLES 131 
#define  KVM_VGIC_V3_ADDR_TYPE_DIST 130 
#define  KVM_VGIC_V3_ADDR_TYPE_REDIST 129 
#define  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION 128 
 int VGIC_LEVEL_INFO_LINE_LEVEL ; 
 int vgic_v3_has_attr_regs (struct kvm_device*,struct kvm_device_attr*) ; 

__attribute__((used)) static int vgic_v3_has_attr(struct kvm_device *dev,
			    struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_ARM_VGIC_GRP_ADDR:
		switch (attr->attr) {
		case KVM_VGIC_V3_ADDR_TYPE_DIST:
		case KVM_VGIC_V3_ADDR_TYPE_REDIST:
		case KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION:
			return 0;
		}
		break;
	case KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	case KVM_DEV_ARM_VGIC_GRP_REDIST_REGS:
	case KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS:
		return vgic_v3_has_attr_regs(dev, attr);
	case KVM_DEV_ARM_VGIC_GRP_NR_IRQS:
		return 0;
	case KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO: {
		if (((attr->attr & KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK) >>
		      KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT) ==
		      VGIC_LEVEL_INFO_LINE_LEVEL)
			return 0;
		break;
	}
	case KVM_DEV_ARM_VGIC_GRP_CTRL:
		switch (attr->attr) {
		case KVM_DEV_ARM_VGIC_CTRL_INIT:
			return 0;
		case KVM_DEV_ARM_VGIC_SAVE_PENDING_TABLES:
			return 0;
		}
	}
	return -ENXIO;
}