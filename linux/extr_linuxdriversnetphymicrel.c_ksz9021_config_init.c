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
struct device {struct device* parent; struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZPHY_CLK_CONTROL_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZPHY_RX_DATA_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZPHY_TX_DATA_PAD_SKEW ; 
 int /*<<< orphan*/  ksz9021_load_values_from_of (struct phy_device*,struct device_node const*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static int ksz9021_config_init(struct phy_device *phydev)
{
	const struct device *dev = &phydev->mdio.dev;
	const struct device_node *of_node = dev->of_node;
	const struct device *dev_walker;

	/* The Micrel driver has a deprecated option to place phy OF
	 * properties in the MAC node. Walk up the tree of devices to
	 * find a device with an OF node.
	 */
	dev_walker = &phydev->mdio.dev;
	do {
		of_node = dev_walker->of_node;
		dev_walker = dev_walker->parent;

	} while (!of_node && dev_walker);

	if (of_node) {
		ksz9021_load_values_from_of(phydev, of_node,
				    MII_KSZPHY_CLK_CONTROL_PAD_SKEW,
				    "txen-skew-ps", "txc-skew-ps",
				    "rxdv-skew-ps", "rxc-skew-ps");
		ksz9021_load_values_from_of(phydev, of_node,
				    MII_KSZPHY_RX_DATA_PAD_SKEW,
				    "rxd0-skew-ps", "rxd1-skew-ps",
				    "rxd2-skew-ps", "rxd3-skew-ps");
		ksz9021_load_values_from_of(phydev, of_node,
				    MII_KSZPHY_TX_DATA_PAD_SKEW,
				    "txd0-skew-ps", "txd1-skew-ps",
				    "txd2-skew-ps", "txd3-skew-ps");
	}
	return 0;
}