#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ coreid; } ;
struct ssb_device {TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ SSB_DEV_USB20_HOST ; 
 int /*<<< orphan*/  ssb_hcd_5354wa (struct ssb_device*) ; 
 int ssb_read32 (struct ssb_device*,int) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ssb_hcd_usb20wa(struct ssb_device *dev)
{
	if (dev->id.coreid == SSB_DEV_USB20_HOST) {
		/*
		 * USB 2.0 special considerations:
		 *
		 * In addition to the standard SSB reset sequence, the Host
		 * Control Register must be programmed to bring the USB core
		 * and various phy components out of reset.
		 */
		ssb_write32(dev, 0x200, 0x7ff);

		/* Change Flush control reg */
		ssb_write32(dev, 0x400, ssb_read32(dev, 0x400) & ~8);
		ssb_read32(dev, 0x400);

		/* Change Shim control reg */
		ssb_write32(dev, 0x304, ssb_read32(dev, 0x304) & ~0x100);
		ssb_read32(dev, 0x304);

		udelay(1);

		ssb_hcd_5354wa(dev);
	}
}