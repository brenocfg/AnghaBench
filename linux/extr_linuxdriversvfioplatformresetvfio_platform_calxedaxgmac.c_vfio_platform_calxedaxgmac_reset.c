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
struct vfio_platform_region {scalar_t__ ioaddr; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct vfio_platform_device {struct vfio_platform_region* regions; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ XGMAC_DMA_INTR_ENA ; 
 scalar_t__ ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xgmac_mac_disable (scalar_t__) ; 

__attribute__((used)) static int vfio_platform_calxedaxgmac_reset(struct vfio_platform_device *vdev)
{
	struct vfio_platform_region *reg = &vdev->regions[0];

	if (!reg->ioaddr) {
		reg->ioaddr =
			ioremap_nocache(reg->addr, reg->size);
		if (!reg->ioaddr)
			return -ENOMEM;
	}

	/* disable IRQ */
	writel(0, reg->ioaddr + XGMAC_DMA_INTR_ENA);

	/* Disable the MAC core */
	xgmac_mac_disable(reg->ioaddr);

	return 0;
}