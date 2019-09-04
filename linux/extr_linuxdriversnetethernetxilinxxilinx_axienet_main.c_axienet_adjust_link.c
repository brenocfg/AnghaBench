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
struct phy_device {int speed; int duplex; int link; } ;
struct net_device {int /*<<< orphan*/  dev; struct phy_device* phydev; } ;
struct axienet_local {int last_link; scalar_t__ phy_mode; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_1000BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int XAE_EMMC_LINKSPD_10 ; 
 int XAE_EMMC_LINKSPD_100 ; 
 int XAE_EMMC_LINKSPD_1000 ; 
 int XAE_EMMC_LINKSPEED_MASK ; 
 int /*<<< orphan*/  XAE_EMMC_OFFSET ; 
 int axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_iow (struct axienet_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void axienet_adjust_link(struct net_device *ndev)
{
	u32 emmc_reg;
	u32 link_state;
	u32 setspeed = 1;
	struct axienet_local *lp = netdev_priv(ndev);
	struct phy_device *phy = ndev->phydev;

	link_state = phy->speed | (phy->duplex << 1) | phy->link;
	if (lp->last_link != link_state) {
		if ((phy->speed == SPEED_10) || (phy->speed == SPEED_100)) {
			if (lp->phy_mode == PHY_INTERFACE_MODE_1000BASEX)
				setspeed = 0;
		} else {
			if ((phy->speed == SPEED_1000) &&
			    (lp->phy_mode == PHY_INTERFACE_MODE_MII))
				setspeed = 0;
		}

		if (setspeed == 1) {
			emmc_reg = axienet_ior(lp, XAE_EMMC_OFFSET);
			emmc_reg &= ~XAE_EMMC_LINKSPEED_MASK;

			switch (phy->speed) {
			case SPEED_1000:
				emmc_reg |= XAE_EMMC_LINKSPD_1000;
				break;
			case SPEED_100:
				emmc_reg |= XAE_EMMC_LINKSPD_100;
				break;
			case SPEED_10:
				emmc_reg |= XAE_EMMC_LINKSPD_10;
				break;
			default:
				dev_err(&ndev->dev, "Speed other than 10, 100 "
					"or 1Gbps is not supported\n");
				break;
			}

			axienet_iow(lp, XAE_EMMC_OFFSET, emmc_reg);
			lp->last_link = link_state;
			phy_print_status(phy);
		} else {
			netdev_err(ndev,
				   "Error setting Axi Ethernet mac speed\n");
		}
	}
}