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
struct usbnet {TYPE_2__* udev; TYPE_1__* net; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int mcs7830_hif_set_mac_address (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs7830_hif_update_config (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_hif_update_multicast_hash (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_rev_C_fixup (struct usbnet*) ; 
 int mcs7830_set_autoneg (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcs7830_apply_base_config(struct usbnet *dev)
{
	int ret;

	/* re-configure known MAC (suspend case etc.) */
	ret = mcs7830_hif_set_mac_address(dev, dev->net->dev_addr);
	if (ret) {
		dev_info(&dev->udev->dev, "Cannot set MAC address\n");
		goto out;
	}

	/* Set up PHY */
	ret = mcs7830_set_autoneg(dev, 0);
	if (ret) {
		dev_info(&dev->udev->dev, "Cannot set autoneg\n");
		goto out;
	}

	mcs7830_hif_update_multicast_hash(dev);
	mcs7830_hif_update_config(dev);

	mcs7830_rev_C_fixup(dev);
	ret = 0;
out:
	return ret;
}