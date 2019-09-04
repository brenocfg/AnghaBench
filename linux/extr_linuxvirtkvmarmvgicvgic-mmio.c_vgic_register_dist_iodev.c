#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgic_io_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * redist_vcpu; int /*<<< orphan*/  iodev_type; int /*<<< orphan*/  base_addr; } ;
struct TYPE_3__ {struct vgic_io_device dist_iodev; } ;
struct TYPE_4__ {TYPE_1__ vgic; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;
typedef  enum vgic_type { ____Placeholder_vgic_type } vgic_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IODEV_DIST ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
#define  VGIC_V2 129 
#define  VGIC_V3 128 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int vgic_v2_init_dist_iodev (struct vgic_io_device*) ; 
 unsigned int vgic_v3_init_dist_iodev (struct vgic_io_device*) ; 

int vgic_register_dist_iodev(struct kvm *kvm, gpa_t dist_base_address,
			     enum vgic_type type)
{
	struct vgic_io_device *io_device = &kvm->arch.vgic.dist_iodev;
	int ret = 0;
	unsigned int len;

	switch (type) {
	case VGIC_V2:
		len = vgic_v2_init_dist_iodev(io_device);
		break;
	case VGIC_V3:
		len = vgic_v3_init_dist_iodev(io_device);
		break;
	default:
		BUG_ON(1);
	}

	io_device->base_addr = dist_base_address;
	io_device->iodev_type = IODEV_DIST;
	io_device->redist_vcpu = NULL;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_register_dev(kvm, KVM_MMIO_BUS, dist_base_address,
				      len, &io_device->dev);
	mutex_unlock(&kvm->slots_lock);

	return ret;
}