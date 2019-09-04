#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sh_eth_private {int duplex; TYPE_4__* cd; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_id; TYPE_3__* mii_bus; scalar_t__ speed; scalar_t__ link; } ;
struct phy_device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phy_id ;
struct TYPE_8__ {scalar_t__ register_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct phy_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* PHY_ID_FMT ; 
 int PTR_ERR (struct phy_device*) ; 
 scalar_t__ SH_ETH_REG_GIGABIT ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_adjust_link ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_phy_init(struct net_device *ndev)
{
	struct device_node *np = ndev->dev.parent->of_node;
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct phy_device *phydev;

	mdp->link = 0;
	mdp->speed = 0;
	mdp->duplex = -1;

	/* Try connect to PHY */
	if (np) {
		struct device_node *pn;

		pn = of_parse_phandle(np, "phy-handle", 0);
		phydev = of_phy_connect(ndev, pn,
					sh_eth_adjust_link, 0,
					mdp->phy_interface);

		of_node_put(pn);
		if (!phydev)
			phydev = ERR_PTR(-ENOENT);
	} else {
		char phy_id[MII_BUS_ID_SIZE + 3];

		snprintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
			 mdp->mii_bus->id, mdp->phy_id);

		phydev = phy_connect(ndev, phy_id, sh_eth_adjust_link,
				     mdp->phy_interface);
	}

	if (IS_ERR(phydev)) {
		netdev_err(ndev, "failed to connect PHY\n");
		return PTR_ERR(phydev);
	}

	/* mask with MAC supported features */
	if (mdp->cd->register_type != SH_ETH_REG_GIGABIT) {
		int err = phy_set_max_speed(phydev, SPEED_100);
		if (err) {
			netdev_err(ndev, "failed to limit PHY to 100 Mbit/s\n");
			phy_disconnect(phydev);
			return err;
		}
	}

	phy_attached_info(phydev);

	return 0;
}