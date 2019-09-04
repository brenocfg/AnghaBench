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
typedef  int /*<<< orphan*/  u32 ;
struct phylink {scalar_t__ link_an_mode; int /*<<< orphan*/  link_interface; int /*<<< orphan*/  netdev; } ;
struct phy_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MLO_AN_FIXED ; 
 scalar_t__ MLO_AN_INBAND ; 
 scalar_t__ MLO_AN_PHY ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_attach (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_detach (struct phy_device*) ; 
 scalar_t__ phy_interface_mode_is_8023z (int /*<<< orphan*/ ) ; 
 int phylink_bringup_phy (struct phylink*,struct phy_device*) ; 

int phylink_of_phy_connect(struct phylink *pl, struct device_node *dn,
			   u32 flags)
{
	struct device_node *phy_node;
	struct phy_device *phy_dev;
	int ret;

	/* Fixed links and 802.3z are handled without needing a PHY */
	if (pl->link_an_mode == MLO_AN_FIXED ||
	    (pl->link_an_mode == MLO_AN_INBAND &&
	     phy_interface_mode_is_8023z(pl->link_interface)))
		return 0;

	phy_node = of_parse_phandle(dn, "phy-handle", 0);
	if (!phy_node)
		phy_node = of_parse_phandle(dn, "phy", 0);
	if (!phy_node)
		phy_node = of_parse_phandle(dn, "phy-device", 0);

	if (!phy_node) {
		if (pl->link_an_mode == MLO_AN_PHY)
			return -ENODEV;
		return 0;
	}

	phy_dev = of_phy_attach(pl->netdev, phy_node, flags,
				pl->link_interface);
	/* We're done with the phy_node handle */
	of_node_put(phy_node);

	if (!phy_dev)
		return -ENODEV;

	ret = phylink_bringup_phy(pl, phy_dev);
	if (ret)
		phy_detach(phy_dev);

	return ret;
}