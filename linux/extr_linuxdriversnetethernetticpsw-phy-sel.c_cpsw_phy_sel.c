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
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct cpsw_phy_sel_priv {int /*<<< orphan*/  (* cpsw_phy_sel ) (struct cpsw_phy_sel_priv*,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct cpsw_phy_sel_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  match ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct cpsw_phy_sel_priv*,int /*<<< orphan*/ ,int) ; 

void cpsw_phy_sel(struct device *dev, phy_interface_t phy_mode, int slave)
{
	struct device_node *node;
	struct cpsw_phy_sel_priv *priv;

	node = of_parse_phandle(dev->of_node, "cpsw-phy-sel", 0);
	if (!node) {
		node = of_get_child_by_name(dev->of_node, "cpsw-phy-sel");
		if (!node) {
			dev_err(dev, "Phy mode driver DT not found\n");
			return;
		}
	}

	dev = bus_find_device(&platform_bus_type, NULL, node, match);
	if (!dev) {
		dev_err(dev, "unable to find platform device for %pOF\n", node);
		goto out;
	}

	priv = dev_get_drvdata(dev);

	priv->cpsw_phy_sel(priv, phy_mode, slave);

	put_device(dev);
out:
	of_node_put(node);
}