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
struct usbnet {int /*<<< orphan*/  phy_mutex; int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DM_SHARED_ADDR ; 
 int /*<<< orphan*/  DM_SHARED_CTRL ; 
 int /*<<< orphan*/  DM_SHARED_DATA ; 
 int DM_TIMEOUT ; 
 int EIO ; 
 int dm_read (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int dm_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dm_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dm_read_shared_word(struct usbnet *dev, int phy, u8 reg, __le16 *value)
{
	int ret, i;

	mutex_lock(&dev->phy_mutex);

	dm_write_reg(dev, DM_SHARED_ADDR, phy ? (reg | 0x40) : reg);
	dm_write_reg(dev, DM_SHARED_CTRL, phy ? 0xc : 0x4);

	for (i = 0; i < DM_TIMEOUT; i++) {
		u8 tmp = 0;

		udelay(1);
		ret = dm_read_reg(dev, DM_SHARED_CTRL, &tmp);
		if (ret < 0)
			goto out;

		/* ready */
		if ((tmp & 1) == 0)
			break;
	}

	if (i == DM_TIMEOUT) {
		netdev_err(dev->net, "%s read timed out!\n", phy ? "phy" : "eeprom");
		ret = -EIO;
		goto out;
	}

	dm_write_reg(dev, DM_SHARED_CTRL, 0x0);
	ret = dm_read(dev, DM_SHARED_DATA, 2, value);

	netdev_dbg(dev->net, "read shared %d 0x%02x returned 0x%04x, %d\n",
		   phy, reg, *value, ret);

 out:
	mutex_unlock(&dev->phy_mutex);
	return ret;
}