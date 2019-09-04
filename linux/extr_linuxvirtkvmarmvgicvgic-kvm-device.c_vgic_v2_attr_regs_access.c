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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_reg_attr {int /*<<< orphan*/  addr; struct kvm_vcpu* vcpu; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_device_attr {int group; } ;
struct kvm_device {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  KVM_DEV_ARM_VGIC_GRP_CPU_REGS 129 
#define  KVM_DEV_ARM_VGIC_GRP_DIST_REGS 128 
 int /*<<< orphan*/  lock_all_vcpus (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_all_vcpus (TYPE_1__*) ; 
 int vgic_init (TYPE_1__*) ; 
 int vgic_v2_cpuif_uaccess (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vgic_v2_dist_uaccess (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vgic_v2_parse_attr (struct kvm_device*,struct kvm_device_attr*,struct vgic_reg_attr*) ; 

__attribute__((used)) static int vgic_v2_attr_regs_access(struct kvm_device *dev,
				    struct kvm_device_attr *attr,
				    u32 *reg, bool is_write)
{
	struct vgic_reg_attr reg_attr;
	gpa_t addr;
	struct kvm_vcpu *vcpu;
	int ret;

	ret = vgic_v2_parse_attr(dev, attr, &reg_attr);
	if (ret)
		return ret;

	vcpu = reg_attr.vcpu;
	addr = reg_attr.addr;

	mutex_lock(&dev->kvm->lock);

	ret = vgic_init(dev->kvm);
	if (ret)
		goto out;

	if (!lock_all_vcpus(dev->kvm)) {
		ret = -EBUSY;
		goto out;
	}

	switch (attr->group) {
	case KVM_DEV_ARM_VGIC_GRP_CPU_REGS:
		ret = vgic_v2_cpuif_uaccess(vcpu, is_write, addr, reg);
		break;
	case KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
		ret = vgic_v2_dist_uaccess(vcpu, is_write, addr, reg);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	unlock_all_vcpus(dev->kvm);
out:
	mutex_unlock(&dev->kvm->lock);
	return ret;
}