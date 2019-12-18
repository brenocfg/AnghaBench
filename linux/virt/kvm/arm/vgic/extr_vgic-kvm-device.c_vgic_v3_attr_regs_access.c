#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct vgic_reg_attr {int /*<<< orphan*/  addr; struct kvm_vcpu* vcpu; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_device_attr {int group; int attr; } ;
struct kvm_device {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS 131 
#define  KVM_DEV_ARM_VGIC_GRP_DIST_REGS 130 
#define  KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO 129 
#define  KVM_DEV_ARM_VGIC_GRP_REDIST_REGS 128 
 unsigned int KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK ; 
 unsigned int KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT ; 
 unsigned int KVM_DEV_ARM_VGIC_LINE_LEVEL_INTID_MASK ; 
 int KVM_DEV_ARM_VGIC_SYSREG_INSTR_MASK ; 
 unsigned int VGIC_LEVEL_INFO_LINE_LEVEL ; 
 int /*<<< orphan*/  lock_all_vcpus (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_all_vcpus (TYPE_1__*) ; 
 int /*<<< orphan*/  vgic_initialized (TYPE_1__*) ; 
 int vgic_v3_cpu_sysregs_uaccess (struct kvm_vcpu*,int,int,int*) ; 
 int vgic_v3_dist_uaccess (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int*) ; 
 int vgic_v3_line_level_info_uaccess (struct kvm_vcpu*,int,unsigned int,int*) ; 
 int vgic_v3_parse_attr (struct kvm_device*,struct kvm_device_attr*,struct vgic_reg_attr*) ; 
 int vgic_v3_redist_uaccess (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vgic_v3_attr_regs_access(struct kvm_device *dev,
				    struct kvm_device_attr *attr,
				    u64 *reg, bool is_write)
{
	struct vgic_reg_attr reg_attr;
	gpa_t addr;
	struct kvm_vcpu *vcpu;
	int ret;
	u32 tmp32;

	ret = vgic_v3_parse_attr(dev, attr, &reg_attr);
	if (ret)
		return ret;

	vcpu = reg_attr.vcpu;
	addr = reg_attr.addr;

	mutex_lock(&dev->kvm->lock);

	if (unlikely(!vgic_initialized(dev->kvm))) {
		ret = -EBUSY;
		goto out;
	}

	if (!lock_all_vcpus(dev->kvm)) {
		ret = -EBUSY;
		goto out;
	}

	switch (attr->group) {
	case KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
		if (is_write)
			tmp32 = *reg;

		ret = vgic_v3_dist_uaccess(vcpu, is_write, addr, &tmp32);
		if (!is_write)
			*reg = tmp32;
		break;
	case KVM_DEV_ARM_VGIC_GRP_REDIST_REGS:
		if (is_write)
			tmp32 = *reg;

		ret = vgic_v3_redist_uaccess(vcpu, is_write, addr, &tmp32);
		if (!is_write)
			*reg = tmp32;
		break;
	case KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS: {
		u64 regid;

		regid = (attr->attr & KVM_DEV_ARM_VGIC_SYSREG_INSTR_MASK);
		ret = vgic_v3_cpu_sysregs_uaccess(vcpu, is_write,
						  regid, reg);
		break;
	}
	case KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO: {
		unsigned int info, intid;

		info = (attr->attr & KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK) >>
			KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT;
		if (info == VGIC_LEVEL_INFO_LINE_LEVEL) {
			intid = attr->attr &
				KVM_DEV_ARM_VGIC_LINE_LEVEL_INTID_MASK;
			ret = vgic_v3_line_level_info_uaccess(vcpu, is_write,
							      intid, reg);
		} else {
			ret = -EINVAL;
		}
		break;
	}
	default:
		ret = -EINVAL;
		break;
	}

	unlock_all_vcpus(dev->kvm);
out:
	mutex_unlock(&dev->kvm->lock);
	return ret;
}