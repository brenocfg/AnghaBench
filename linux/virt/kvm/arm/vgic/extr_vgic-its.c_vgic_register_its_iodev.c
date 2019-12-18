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
typedef  int /*<<< orphan*/  u64 ;
struct vgic_io_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  base_addr; struct vgic_its* its; int /*<<< orphan*/  iodev_type; int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  regions; } ;
struct vgic_its {int /*<<< orphan*/  vgic_its_base; struct vgic_io_device iodev; } ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IODEV_ITS ; 
 int /*<<< orphan*/  IS_VGIC_ADDR_UNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int /*<<< orphan*/  KVM_VGIC_V3_ITS_SIZE ; 
 int /*<<< orphan*/  its_registers ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_io_gic_ops ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vgic_register_its_iodev(struct kvm *kvm, struct vgic_its *its,
				   u64 addr)
{
	struct vgic_io_device *iodev = &its->iodev;
	int ret;

	mutex_lock(&kvm->slots_lock);
	if (!IS_VGIC_ADDR_UNDEF(its->vgic_its_base)) {
		ret = -EBUSY;
		goto out;
	}

	its->vgic_its_base = addr;
	iodev->regions = its_registers;
	iodev->nr_regions = ARRAY_SIZE(its_registers);
	kvm_iodevice_init(&iodev->dev, &kvm_io_gic_ops);

	iodev->base_addr = its->vgic_its_base;
	iodev->iodev_type = IODEV_ITS;
	iodev->its = its;
	ret = kvm_io_bus_register_dev(kvm, KVM_MMIO_BUS, iodev->base_addr,
				      KVM_VGIC_V3_ITS_SIZE, &iodev->dev);
out:
	mutex_unlock(&kvm->slots_lock);

	return ret;
}