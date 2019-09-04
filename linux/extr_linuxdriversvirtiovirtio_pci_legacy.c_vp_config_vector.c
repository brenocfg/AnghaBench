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
typedef  int /*<<< orphan*/  u16 ;
struct virtio_pci_device {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_MSI_CONFIG_VECTOR ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u16 vp_config_vector(struct virtio_pci_device *vp_dev, u16 vector)
{
	/* Setup the vector used for configuration events */
	iowrite16(vector, vp_dev->ioaddr + VIRTIO_MSI_CONFIG_VECTOR);
	/* Verify we had enough resources to assign the vector */
	/* Will also flush the write out to device */
	return ioread16(vp_dev->ioaddr + VIRTIO_MSI_CONFIG_VECTOR);
}