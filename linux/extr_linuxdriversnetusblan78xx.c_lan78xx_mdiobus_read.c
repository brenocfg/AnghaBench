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
struct mii_bus {struct lan78xx_net* priv; } ;
struct lan78xx_net {int /*<<< orphan*/  intf; int /*<<< orphan*/  phy_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ACC ; 
 int /*<<< orphan*/  MII_DATA ; 
 int /*<<< orphan*/  MII_READ ; 
 int lan78xx_phy_wait_not_busy (struct lan78xx_net*) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int mii_access (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_mdiobus_read(struct mii_bus *bus, int phy_id, int idx)
{
	struct lan78xx_net *dev = bus->priv;
	u32 val, addr;
	int ret;

	ret = usb_autopm_get_interface(dev->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = lan78xx_phy_wait_not_busy(dev);
	if (ret < 0)
		goto done;

	/* set the address, index & direction (read from PHY) */
	addr = mii_access(phy_id, idx, MII_READ);
	ret = lan78xx_write_reg(dev, MII_ACC, addr);

	ret = lan78xx_phy_wait_not_busy(dev);
	if (ret < 0)
		goto done;

	ret = lan78xx_read_reg(dev, MII_DATA, &val);

	ret = (int)(val & 0xFFFF);

done:
	mutex_unlock(&dev->phy_mutex);
	usb_autopm_put_interface(dev->intf);

	return ret;
}