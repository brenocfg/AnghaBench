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
 int SR_SWRESET_CLEAR ; 
 int SR_SWRESET_IPPD ; 
 int SR_SWRESET_IPRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sr_sw_reset (struct usbnet*,int) ; 

__attribute__((used)) static int sr9800_phy_powerup(struct usbnet *dev)
{
	int ret;

	/* set the embedded Ethernet PHY in power-down state */
	ret = sr_sw_reset(dev, SR_SWRESET_IPPD | SR_SWRESET_IPRL);
	if (ret < 0) {
		netdev_err(dev->net, "Failed to power down PHY : %d\n", ret);
		return ret;
	}
	msleep(20);

	/* set the embedded Ethernet PHY in power-up state */
	ret = sr_sw_reset(dev, SR_SWRESET_IPRL);
	if (ret < 0) {
		netdev_err(dev->net, "Failed to reset PHY: %d\n", ret);
		return ret;
	}
	msleep(600);

	/* set the embedded Ethernet PHY in reset state */
	ret = sr_sw_reset(dev, SR_SWRESET_CLEAR);
	if (ret < 0) {
		netdev_err(dev->net, "Failed to power up PHY: %d\n", ret);
		return ret;
	}
	msleep(20);

	/* set the embedded Ethernet PHY in power-up state */
	ret = sr_sw_reset(dev, SR_SWRESET_IPRL);
	if (ret < 0) {
		netdev_err(dev->net, "Failed to reset PHY: %d\n", ret);
		return ret;
	}

	return 0;
}