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
typedef  int u32 ;
struct usbnet {TYPE_1__* net; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_FILTX ; 
 int ADDR_FILTX_FB_VALID ; 
 scalar_t__ RX_ADDRH ; 
 scalar_t__ RX_ADDRL ; 
 int /*<<< orphan*/  netdev_warn (TYPE_1__*,char*,int) ; 
 int smsc75xx_write_reg (struct usbnet*,scalar_t__,int) ; 

__attribute__((used)) static int smsc75xx_set_mac_address(struct usbnet *dev)
{
	u32 addr_lo = dev->net->dev_addr[0] | dev->net->dev_addr[1] << 8 |
		dev->net->dev_addr[2] << 16 | dev->net->dev_addr[3] << 24;
	u32 addr_hi = dev->net->dev_addr[4] | dev->net->dev_addr[5] << 8;

	int ret = smsc75xx_write_reg(dev, RX_ADDRH, addr_hi);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to write RX_ADDRH: %d\n", ret);
		return ret;
	}

	ret = smsc75xx_write_reg(dev, RX_ADDRL, addr_lo);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to write RX_ADDRL: %d\n", ret);
		return ret;
	}

	addr_hi |= ADDR_FILTX_FB_VALID;
	ret = smsc75xx_write_reg(dev, ADDR_FILTX, addr_hi);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to write ADDR_FILTX: %d\n", ret);
		return ret;
	}

	ret = smsc75xx_write_reg(dev, ADDR_FILTX + 4, addr_lo);
	if (ret < 0)
		netdev_warn(dev->net, "Failed to write ADDR_FILTX+4: %d\n", ret);

	return ret;
}