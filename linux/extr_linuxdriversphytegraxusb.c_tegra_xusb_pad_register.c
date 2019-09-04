#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct tegra_xusb_pad {struct tegra_xusb_lane** lanes; struct tegra_xusb_lane* provider; TYPE_4__ dev; TYPE_3__* padctl; TYPE_2__* ops; TYPE_1__* soc; } ;
struct tegra_xusb_lane {int /*<<< orphan*/  list; } ;
struct phy_ops {int dummy; } ;
struct phy {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  lane ;
struct TYPE_9__ {int /*<<< orphan*/  lanes; } ;
struct TYPE_8__ {struct tegra_xusb_lane* (* probe ) (struct tegra_xusb_pad*,struct device_node*,unsigned int) ;} ;
struct TYPE_7__ {unsigned int num_lanes; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tegra_xusb_lane*) ; 
 int PTR_ERR (struct tegra_xusb_lane*) ; 
 struct tegra_xusb_lane** devm_kcalloc (TYPE_4__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct tegra_xusb_lane* of_phy_provider_register_full (TYPE_4__*,struct device_node*,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_create (TYPE_4__*,struct device_node*,struct phy_ops const*) ; 
 int /*<<< orphan*/  phy_destroy (struct tegra_xusb_lane*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct tegra_xusb_lane*,struct tegra_xusb_lane*) ; 
 struct tegra_xusb_lane* stub1 (struct tegra_xusb_pad*,struct device_node*,unsigned int) ; 
 int /*<<< orphan*/  tegra_xusb_lane_destroy (struct tegra_xusb_lane*) ; 
 struct device_node* tegra_xusb_pad_find_phy_node (struct tegra_xusb_pad*,unsigned int) ; 
 int /*<<< orphan*/  tegra_xusb_pad_of_xlate ; 

int tegra_xusb_pad_register(struct tegra_xusb_pad *pad,
			    const struct phy_ops *ops)
{
	struct device_node *children;
	struct phy *lane;
	unsigned int i;
	int err;

	children = of_get_child_by_name(pad->dev.of_node, "lanes");
	if (!children)
		return -ENODEV;

	pad->lanes = devm_kcalloc(&pad->dev, pad->soc->num_lanes, sizeof(lane),
				  GFP_KERNEL);
	if (!pad->lanes) {
		of_node_put(children);
		return -ENOMEM;
	}

	for (i = 0; i < pad->soc->num_lanes; i++) {
		struct device_node *np = tegra_xusb_pad_find_phy_node(pad, i);
		struct tegra_xusb_lane *lane;

		/* skip disabled lanes */
		if (!np || !of_device_is_available(np)) {
			of_node_put(np);
			continue;
		}

		pad->lanes[i] = phy_create(&pad->dev, np, ops);
		if (IS_ERR(pad->lanes[i])) {
			err = PTR_ERR(pad->lanes[i]);
			of_node_put(np);
			goto remove;
		}

		lane = pad->ops->probe(pad, np, i);
		if (IS_ERR(lane)) {
			phy_destroy(pad->lanes[i]);
			err = PTR_ERR(lane);
			goto remove;
		}

		list_add_tail(&lane->list, &pad->padctl->lanes);
		phy_set_drvdata(pad->lanes[i], lane);
	}

	pad->provider = of_phy_provider_register_full(&pad->dev, children,
						      tegra_xusb_pad_of_xlate);
	if (IS_ERR(pad->provider)) {
		err = PTR_ERR(pad->provider);
		goto remove;
	}

	return 0;

remove:
	while (i--)
		tegra_xusb_lane_destroy(pad->lanes[i]);

	of_node_put(children);

	return err;
}