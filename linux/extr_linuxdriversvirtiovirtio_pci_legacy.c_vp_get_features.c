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
struct virtio_pci_device {scalar_t__ ioaddr; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_PCI_HOST_FEATURES ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

__attribute__((used)) static u64 vp_get_features(struct virtio_device *vdev)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);

	/* When someone needs more than 32 feature bits, we'll need to
	 * steal a bit to indicate that the rest are somewhere else. */
	return ioread32(vp_dev->ioaddr + VIRTIO_PCI_HOST_FEATURES);
}