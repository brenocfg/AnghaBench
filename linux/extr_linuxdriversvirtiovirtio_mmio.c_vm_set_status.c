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
typedef  scalar_t__ u8 ;
struct virtio_mmio_device {scalar_t__ base; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VIRTIO_MMIO_STATUS ; 
 struct virtio_mmio_device* to_virtio_mmio_device (struct virtio_device*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vm_set_status(struct virtio_device *vdev, u8 status)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vdev);

	/* We should never be setting status to 0. */
	BUG_ON(status == 0);

	writel(status, vm_dev->base + VIRTIO_MMIO_STATUS);
}