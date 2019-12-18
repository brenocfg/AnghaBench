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
struct kvm_coalesced_mmio_zone {int pio; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct kvm_coalesced_mmio_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  dev; struct kvm_coalesced_mmio_zone zone; struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  slots_lock; int /*<<< orphan*/  coalesced_zones; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int /*<<< orphan*/  coalesced_mmio_ops ; 
 int /*<<< orphan*/  kfree (struct kvm_coalesced_mmio_dev*) ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kvm_coalesced_mmio_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kvm_vm_ioctl_register_coalesced_mmio(struct kvm *kvm,
					 struct kvm_coalesced_mmio_zone *zone)
{
	int ret;
	struct kvm_coalesced_mmio_dev *dev;

	if (zone->pio != 1 && zone->pio != 0)
		return -EINVAL;

	dev = kzalloc(sizeof(struct kvm_coalesced_mmio_dev),
		      GFP_KERNEL_ACCOUNT);
	if (!dev)
		return -ENOMEM;

	kvm_iodevice_init(&dev->dev, &coalesced_mmio_ops);
	dev->kvm = kvm;
	dev->zone = *zone;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_register_dev(kvm,
				zone->pio ? KVM_PIO_BUS : KVM_MMIO_BUS,
				zone->addr, zone->size, &dev->dev);
	if (ret < 0)
		goto out_free_dev;
	list_add_tail(&dev->list, &kvm->coalesced_zones);
	mutex_unlock(&kvm->slots_lock);

	return 0;

out_free_dev:
	mutex_unlock(&kvm->slots_lock);
	kfree(dev);

	return ret;
}