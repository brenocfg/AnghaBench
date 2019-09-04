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
struct niu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int niu_get_of_props(struct niu *np)
{
#ifdef CONFIG_SPARC64
	struct net_device *dev = np->dev;
	struct device_node *dp;
	const char *phy_type;
	const u8 *mac_addr;
	const char *model;
	int prop_len;

	if (np->parent->plat_type == PLAT_TYPE_NIU)
		dp = np->op->dev.of_node;
	else
		dp = pci_device_to_OF_node(np->pdev);

	phy_type = of_get_property(dp, "phy-type", &prop_len);
	if (!phy_type) {
		netdev_err(dev, "%pOF: OF node lacks phy-type property\n", dp);
		return -EINVAL;
	}

	if (!strcmp(phy_type, "none"))
		return -ENODEV;

	strcpy(np->vpd.phy_type, phy_type);

	if (niu_phy_type_prop_decode(np, np->vpd.phy_type)) {
		netdev_err(dev, "%pOF: Illegal phy string [%s]\n",
			   dp, np->vpd.phy_type);
		return -EINVAL;
	}

	mac_addr = of_get_property(dp, "local-mac-address", &prop_len);
	if (!mac_addr) {
		netdev_err(dev, "%pOF: OF node lacks local-mac-address property\n",
			   dp);
		return -EINVAL;
	}
	if (prop_len != dev->addr_len) {
		netdev_err(dev, "%pOF: OF MAC address prop len (%d) is wrong\n",
			   dp, prop_len);
	}
	memcpy(dev->dev_addr, mac_addr, dev->addr_len);
	if (!is_valid_ether_addr(&dev->dev_addr[0])) {
		netdev_err(dev, "%pOF: OF MAC address is invalid\n", dp);
		netdev_err(dev, "%pOF: [ %pM ]\n", dp, dev->dev_addr);
		return -EINVAL;
	}

	model = of_get_property(dp, "model", &prop_len);

	if (model)
		strcpy(np->vpd.model, model);

	if (of_find_property(dp, "hot-swappable-phy", &prop_len)) {
		np->flags |= (NIU_FLAGS_10G | NIU_FLAGS_FIBER |
			NIU_FLAGS_HOTPLUG_PHY);
	}

	return 0;
#else
	return -EINVAL;
#endif
}