#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {TYPE_1__* drv; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;
struct mtk_mac {size_t id; } ;
struct mtk_eth {scalar_t__* link; TYPE_2__* phy; int /*<<< orphan*/  dev; int /*<<< orphan*/ * netdev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {struct phy_device** phy; int /*<<< orphan*/ ** phy_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PHY_GBIT_FEATURES ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_phy_link_adjust ; 
 int of_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct phy_device* of_phy_connect (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int mtk_connect_phy_node(struct mtk_eth *eth, struct mtk_mac *mac,
			 struct device_node *phy_node)
{
	const __be32 *_port = NULL;
	struct phy_device *phydev;
	int phy_mode, port;

	_port = of_get_property(phy_node, "reg", NULL);

	if (!_port || (be32_to_cpu(*_port) >= 0x20)) {
		pr_err("%s: invalid port id\n", phy_node->name);
		return -EINVAL;
	}
	port = be32_to_cpu(*_port);
	phy_mode = of_get_phy_mode(phy_node);
	if (phy_mode < 0) {
		dev_err(eth->dev, "incorrect phy-mode %d\n", phy_mode);
		eth->phy->phy_node[port] = NULL;
		return -EINVAL;
	}

	phydev = of_phy_connect(eth->netdev[mac->id], phy_node,
				mtk_phy_link_adjust, 0, phy_mode);
	if (!phydev) {
		dev_err(eth->dev, "could not connect to PHY\n");
		eth->phy->phy_node[port] = NULL;
		return -ENODEV;
	}

	phydev->supported &= PHY_GBIT_FEATURES;
	phydev->advertising = phydev->supported;

	dev_info(eth->dev,
		 "connected port %d to PHY at %s [uid=%08x, driver=%s]\n",
		 port, phydev_name(phydev), phydev->phy_id,
		 phydev->drv->name);

	eth->phy->phy[port] = phydev;
	eth->link[port] = 0;

	return 0;
}