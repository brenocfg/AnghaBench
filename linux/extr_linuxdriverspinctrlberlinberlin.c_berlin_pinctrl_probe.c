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
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct berlin_pinctrl_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int berlin_pinctrl_probe_regmap (struct platform_device*,struct berlin_pinctrl_desc const*,struct regmap*) ; 
 struct device_node* of_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

int berlin_pinctrl_probe(struct platform_device *pdev,
			 const struct berlin_pinctrl_desc *desc)
{
	struct device *dev = &pdev->dev;
	struct device_node *parent_np = of_get_parent(dev->of_node);
	struct regmap *regmap = syscon_node_to_regmap(parent_np);

	of_node_put(parent_np);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return berlin_pinctrl_probe_regmap(pdev, desc, regmap);
}