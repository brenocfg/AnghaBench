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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct mii_phy {int status; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ANADV ; 
 int MII_NWAY_CSMA_CD ; 
 int MII_NWAY_T ; 
 int MII_NWAY_TX ; 
 int MII_NWAY_TX_FDX ; 
 int MII_NWAY_T_FDX ; 
 int /*<<< orphan*/  MII_STATUS ; 
 int MII_STAT_CAN_T ; 
 int MII_STAT_CAN_TX ; 
 int MII_STAT_CAN_TX_FDX ; 
 int MII_STAT_CAN_T_FDX ; 
 int mdio_read (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sis900_set_capability(struct net_device *net_dev, struct mii_phy *phy)
{
	u16 cap;
	u16 status;

	status = mdio_read(net_dev, phy->phy_addr, MII_STATUS);
	status = mdio_read(net_dev, phy->phy_addr, MII_STATUS);

	cap = MII_NWAY_CSMA_CD |
		((phy->status & MII_STAT_CAN_TX_FDX)? MII_NWAY_TX_FDX:0) |
		((phy->status & MII_STAT_CAN_TX)    ? MII_NWAY_TX:0) |
		((phy->status & MII_STAT_CAN_T_FDX) ? MII_NWAY_T_FDX:0)|
		((phy->status & MII_STAT_CAN_T)     ? MII_NWAY_T:0);

	mdio_write(net_dev, phy->phy_addr, MII_ANADV, cap);
}