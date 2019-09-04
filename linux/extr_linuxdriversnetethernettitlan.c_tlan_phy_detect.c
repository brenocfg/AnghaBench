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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct tlan_priv {int phy_num; scalar_t__* phy; TYPE_1__* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  MII_GEN_ID_HI ; 
 int /*<<< orphan*/  MII_GEN_ID_LO ; 
 int TLAN_ADAPTER_UNMANAGED_PHY ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 scalar_t__ TLAN_PHY_MAX_ADDR ; 
 scalar_t__ TLAN_PHY_NONE ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tlan_mii_read_reg (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void tlan_phy_detect(struct net_device *dev)
{
	struct tlan_priv *priv = netdev_priv(dev);
	u16		control;
	u16		hi;
	u16		lo;
	u32		phy;

	if (priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY) {
		priv->phy_num = 0xffff;
		return;
	}

	tlan_mii_read_reg(dev, TLAN_PHY_MAX_ADDR, MII_GEN_ID_HI, &hi);

	if (hi != 0xffff)
		priv->phy[0] = TLAN_PHY_MAX_ADDR;
	else
		priv->phy[0] = TLAN_PHY_NONE;

	priv->phy[1] = TLAN_PHY_NONE;
	for (phy = 0; phy <= TLAN_PHY_MAX_ADDR; phy++) {
		tlan_mii_read_reg(dev, phy, MII_GEN_CTL, &control);
		tlan_mii_read_reg(dev, phy, MII_GEN_ID_HI, &hi);
		tlan_mii_read_reg(dev, phy, MII_GEN_ID_LO, &lo);
		if ((control != 0xffff) ||
		    (hi != 0xffff) || (lo != 0xffff)) {
			TLAN_DBG(TLAN_DEBUG_GNRL,
				 "PHY found at %02x %04x %04x %04x\n",
				 phy, control, hi, lo);
			if ((priv->phy[1] == TLAN_PHY_NONE) &&
			    (phy != TLAN_PHY_MAX_ADDR)) {
				priv->phy[1] = phy;
			}
		}
	}

	if (priv->phy[1] != TLAN_PHY_NONE)
		priv->phy_num = 1;
	else if (priv->phy[0] != TLAN_PHY_NONE)
		priv->phy_num = 0;
	else
		netdev_info(dev, "Cannot initialize device, no PHY was found!\n");

}