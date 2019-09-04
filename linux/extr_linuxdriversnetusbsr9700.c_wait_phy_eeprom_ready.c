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
typedef  int u8 ;
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int EIO ; 
 int EPCR_ERRE ; 
 int /*<<< orphan*/  SR_EPCR ; 
 int SR_SHARE_TIMEOUT ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int sr_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_phy_eeprom_ready(struct usbnet *dev, int phy)
{
	int i;

	for (i = 0; i < SR_SHARE_TIMEOUT; i++) {
		u8 tmp = 0;
		int ret;

		udelay(1);
		ret = sr_read_reg(dev, SR_EPCR, &tmp);
		if (ret < 0)
			return ret;

		/* ready */
		if (!(tmp & EPCR_ERRE))
			return 0;
	}

	netdev_err(dev->net, "%s write timed out!\n", phy ? "phy" : "eeprom");

	return -EIO;
}