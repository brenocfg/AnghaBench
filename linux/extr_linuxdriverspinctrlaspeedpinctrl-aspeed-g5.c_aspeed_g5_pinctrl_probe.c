#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {struct device_node* parent; } ;
struct TYPE_8__ {int number; } ;
struct TYPE_7__ {struct regmap** maps; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 size_t ASPEED_IP_GFX ; 
 size_t ASPEED_IP_LPC ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 TYPE_2__ aspeed_g5_pinctrl_data ; 
 int /*<<< orphan*/  aspeed_g5_pinctrl_desc ; 
 TYPE_3__* aspeed_g5_pins ; 
 int aspeed_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int aspeed_g5_pinctrl_probe(struct platform_device *pdev)
{
	int i;
	struct regmap *map;
	struct device_node *node;

	for (i = 0; i < ARRAY_SIZE(aspeed_g5_pins); i++)
		aspeed_g5_pins[i].number = i;

	node = of_parse_phandle(pdev->dev.of_node, "aspeed,external-nodes", 0);
	map = syscon_node_to_regmap(node);
	of_node_put(node);
	if (IS_ERR(map)) {
		dev_warn(&pdev->dev, "No GFX phandle found, some mux configurations may fail\n");
		map = NULL;
	}
	aspeed_g5_pinctrl_data.maps[ASPEED_IP_GFX] = map;

	node = of_parse_phandle(pdev->dev.of_node, "aspeed,external-nodes", 1);
	if (node) {
		map = syscon_node_to_regmap(node->parent);
		if (IS_ERR(map)) {
			dev_warn(&pdev->dev, "LHC parent is not a syscon, some mux configurations may fail\n");
			map = NULL;
		}
	} else {
		dev_warn(&pdev->dev, "No LHC phandle found, some mux configurations may fail\n");
		map = NULL;
	}
	of_node_put(node);
	aspeed_g5_pinctrl_data.maps[ASPEED_IP_LPC] = map;

	return aspeed_pinctrl_probe(pdev, &aspeed_g5_pinctrl_desc,
			&aspeed_g5_pinctrl_data);
}