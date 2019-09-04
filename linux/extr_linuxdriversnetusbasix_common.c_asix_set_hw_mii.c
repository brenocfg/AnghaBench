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
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_SET_HW_MII ; 
 int asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

int asix_set_hw_mii(struct usbnet *dev, int in_pm)
{
	int ret;
	ret = asix_write_cmd(dev, AX_CMD_SET_HW_MII, 0x0000, 0, 0, NULL, in_pm);
	if (ret < 0)
		netdev_err(dev->net, "Failed to enable hardware MII access\n");
	return ret;
}