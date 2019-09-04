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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HIF_REG_ETHERNET_ADDR ; 
 int mcs7830_get_reg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int mcs7830_hif_get_mac_address(struct usbnet *dev, unsigned char *addr)
{
	int ret = mcs7830_get_reg(dev, HIF_REG_ETHERNET_ADDR, ETH_ALEN, addr);
	if (ret < 0)
		return ret;
	return 0;
}