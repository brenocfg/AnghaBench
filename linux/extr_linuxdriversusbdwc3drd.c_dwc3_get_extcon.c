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
struct extcon_dev {int dummy; } ;
struct dwc3 {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 struct extcon_dev* extcon_find_edev_by_node (struct device_node*) ; 
 struct extcon_dev* extcon_get_edev_by_phandle (struct device*,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_node (struct device_node*,int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct extcon_dev *dwc3_get_extcon(struct dwc3 *dwc)
{
	struct device *dev = dwc->dev;
	struct device_node *np_phy, *np_conn;
	struct extcon_dev *edev;

	if (of_property_read_bool(dev->of_node, "extcon"))
		return extcon_get_edev_by_phandle(dwc->dev, 0);

	np_phy = of_parse_phandle(dev->of_node, "phys", 0);
	np_conn = of_graph_get_remote_node(np_phy, -1, -1);

	if (np_conn)
		edev = extcon_find_edev_by_node(np_conn);
	else
		edev = NULL;

	of_node_put(np_conn);
	of_node_put(np_phy);

	return edev;
}