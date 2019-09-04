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
typedef  int u32 ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int bcma_read32 (struct bcma_device*,int) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void bcma_hcd_usb20_ns_init_hc(struct bcma_device *dev)
{
	u32 val;

	/* Set packet buffer OUT threshold */
	val = bcma_read32(dev, 0x94);
	val &= 0xffff;
	val |= 0x80 << 16;
	bcma_write32(dev, 0x94, val);

	/* Enable break memory transfer */
	val = bcma_read32(dev, 0x9c);
	val |= 1;
	bcma_write32(dev, 0x9c, val);

	/*
	 * Broadcom initializes PHY and then waits to ensure HC is ready to be
	 * configured. In our case the order is reversed. We just initialized
	 * controller and we let HCD initialize PHY, so let's wait (sleep) now.
	 */
	usleep_range(1000, 2000);
}