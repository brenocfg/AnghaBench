#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_set_parent (struct clk*,struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcasp_reparent_fck(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct clk *gfclk, *parent_clk;
	const char *parent_name;
	int ret;

	if (!node)
		return 0;

	parent_name = of_get_property(node, "fck_parent", NULL);
	if (!parent_name)
		return 0;

	dev_warn(&pdev->dev, "Update the bindings to use assigned-clocks!\n");

	gfclk = clk_get(&pdev->dev, "fck");
	if (IS_ERR(gfclk)) {
		dev_err(&pdev->dev, "failed to get fck\n");
		return PTR_ERR(gfclk);
	}

	parent_clk = clk_get(NULL, parent_name);
	if (IS_ERR(parent_clk)) {
		dev_err(&pdev->dev, "failed to get parent clock\n");
		ret = PTR_ERR(parent_clk);
		goto err1;
	}

	ret = clk_set_parent(gfclk, parent_clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to reparent fck\n");
		goto err2;
	}

err2:
	clk_put(parent_clk);
err1:
	clk_put(gfclk);
	return ret;
}