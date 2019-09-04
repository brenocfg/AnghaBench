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
struct usbnet {int /*<<< orphan*/  net; scalar_t__* data; } ;
struct smsc75xx_priv {int /*<<< orphan*/  suspend_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_PHY_RST ; 
 int PMT_CTL_SUS_MODE ; 
 int PMT_CTL_SUS_MODE_2 ; 
 int PMT_CTL_WUPS ; 
 int /*<<< orphan*/  SUSPEND_SUSPEND2 ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int smsc75xx_read_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc75xx_write_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc75xx_enter_suspend2(struct usbnet *dev)
{
	struct smsc75xx_priv *pdata = (struct smsc75xx_priv *)(dev->data[0]);
	u32 val;
	int ret;

	ret = smsc75xx_read_reg_nopm(dev, PMT_CTL, &val);
	if (ret < 0) {
		netdev_warn(dev->net, "Error reading PMT_CTL\n");
		return ret;
	}

	val &= ~(PMT_CTL_SUS_MODE | PMT_CTL_WUPS | PMT_CTL_PHY_RST);
	val |= PMT_CTL_SUS_MODE_2;

	ret = smsc75xx_write_reg_nopm(dev, PMT_CTL, val);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing PMT_CTL\n");
		return ret;
	}

	pdata->suspend_flags |= SUSPEND_SUSPEND2;

	return 0;
}