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
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int hex2bin (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int usb_string (TYPE_2__*,int,unsigned char*,int) ; 

int usbnet_get_ethernet_addr(struct usbnet *dev, int iMACAddress)
{
	int 		tmp = -1, ret;
	unsigned char	buf [13];

	ret = usb_string(dev->udev, iMACAddress, buf, sizeof buf);
	if (ret == 12)
		tmp = hex2bin(dev->net->dev_addr, buf, 6);
	if (tmp < 0) {
		dev_dbg(&dev->udev->dev,
			"bad MAC string %d fetch, %d\n", iMACAddress, tmp);
		if (ret >= 0)
			ret = -EINVAL;
		return ret;
	}
	return 0;
}