#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mxs_saif {scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_SAIF_CTRL_BITCLK_MULT_RATE ; 
 int EEXIST ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 scalar_t__ SAIF_CTRL ; 
 int /*<<< orphan*/  __clk_get_name (int /*<<< orphan*/ ) ; 
 struct clk* clk_register_divider (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 struct mxs_saif* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mxs_saif_mclk_init(struct platform_device *pdev)
{
	struct mxs_saif *saif = platform_get_drvdata(pdev);
	struct device_node *np = pdev->dev.of_node;
	struct clk *clk;
	int ret;

	clk = clk_register_divider(&pdev->dev, "mxs_saif_mclk",
				   __clk_get_name(saif->clk), 0,
				   saif->base + SAIF_CTRL,
				   BP_SAIF_CTRL_BITCLK_MULT_RATE, 3,
				   0, NULL);
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		if (ret == -EEXIST)
			return 0;
		dev_err(&pdev->dev, "failed to register mclk: %d\n", ret);
		return PTR_ERR(clk);
	}

	ret = of_clk_add_provider(np, of_clk_src_simple_get, clk);
	if (ret)
		return ret;

	return 0;
}