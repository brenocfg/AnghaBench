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
#define  KVM_DEV_ARM_ITS_CTRL_RESET 135 
#define  KVM_DEV_ARM_ITS_RESTORE_TABLES 134 
#define  KVM_DEV_ARM_ITS_SAVE_TABLES 133 
#define  KVM_DEV_ARM_VGIC_CTRL_INIT 132 
#define  KVM_DEV_ARM_VGIC_GRP_ADDR 131 
#define  KVM_DEV_ARM_VGIC_GRP_CTRL 130 
#define  KVM_DEV_ARM_VGIC_GRP_ITS_REGS 129 
#define  KVM_VGIC_ITS_ADDR_TYPE 128 
 int vgic_its_has_attr_regs (struct kvm_device*,struct kvm_device_attr*) ; 

__attribute__((used)) static int vgic_its_has_attr(struct kvm_device *dev,
			     struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_ARM_VGIC_GRP_ADDR:
		switch (attr->attr) {
		case KVM_VGIC_ITS_ADDR_TYPE:
			return 0;
		}
		break;
	case KVM_DEV_ARM_VGIC_GRP_CTRL:
		switch (attr->attr) {
		case KVM_DEV_ARM_VGIC_CTRL_INIT:
			return 0;
		case KVM_DEV_ARM_ITS_CTRL_RESET:
			return 0;
		case KVM_DEV_ARM_ITS_SAVE_TABLES:
			return 0;
		case KVM_DEV_ARM_ITS_RESTORE_TABLES:
			return 0;
		}
		break;
	case KVM_DEV_ARM_VGIC_GRP_ITS_REGS:
		return vgic_its_has_attr_regs(dev, attr);
	}
	return -ENXIO;
}