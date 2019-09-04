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
struct ti_pipe3 {int /*<<< orphan*/  pll_ctrl_base; struct pipe3_dpll_map* dpll_map; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct pipe3_dpll_map {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ti_pipe3_id_table ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int ti_pipe3_get_pll_base(struct ti_pipe3 *phy)
{
	struct resource *res;
	const struct of_device_id *match;
	struct device *dev = phy->dev;
	struct device_node *node = dev->of_node;
	struct platform_device *pdev = to_platform_device(dev);

	if (of_device_is_compatible(node, "ti,phy-pipe3-pcie"))
		return 0;

	match = of_match_device(ti_pipe3_id_table, dev);
	if (!match)
		return -EINVAL;

	phy->dpll_map = (struct pipe3_dpll_map *)match->data;
	if (!phy->dpll_map) {
		dev_err(dev, "no DPLL data\n");
		return -EINVAL;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "pll_ctrl");
	phy->pll_ctrl_base = devm_ioremap_resource(dev, res);
	return PTR_ERR_OR_ZERO(phy->pll_ctrl_base);
}