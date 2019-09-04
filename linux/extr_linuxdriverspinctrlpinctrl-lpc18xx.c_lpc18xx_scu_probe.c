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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lpc18xx_scu_data {int /*<<< orphan*/  pctl; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct lpc18xx_scu_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct lpc18xx_scu_data*) ; 
 int lpc18xx_create_group_func_map (int /*<<< orphan*/ *,struct lpc18xx_scu_data*) ; 
 int /*<<< orphan*/  lpc18xx_scu_desc ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_scu_data*) ; 

__attribute__((used)) static int lpc18xx_scu_probe(struct platform_device *pdev)
{
	struct lpc18xx_scu_data *scu;
	struct resource *res;
	int ret;

	scu = devm_kzalloc(&pdev->dev, sizeof(*scu), GFP_KERNEL);
	if (!scu)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	scu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(scu->base))
		return PTR_ERR(scu->base);

	scu->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(scu->clk)) {
		dev_err(&pdev->dev, "Input clock not found.\n");
		return PTR_ERR(scu->clk);
	}

	ret = lpc18xx_create_group_func_map(&pdev->dev, scu);
	if (ret) {
		dev_err(&pdev->dev, "Unable to create group func map.\n");
		return ret;
	}

	ret = clk_prepare_enable(scu->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		return ret;
	}

	platform_set_drvdata(pdev, scu);

	scu->pctl = devm_pinctrl_register(&pdev->dev, &lpc18xx_scu_desc, scu);
	if (IS_ERR(scu->pctl)) {
		dev_err(&pdev->dev, "Could not register pinctrl driver\n");
		clk_disable_unprepare(scu->clk);
		return PTR_ERR(scu->pctl);
	}

	return 0;
}