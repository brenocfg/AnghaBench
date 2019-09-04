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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct lpass_data {void* pcnoc_sway_clk; void* pcnoc_mport_clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct lpass_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int apq8016_lpass_init(struct platform_device *pdev)
{
	struct lpass_data *drvdata = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	int ret;

	drvdata->pcnoc_mport_clk = devm_clk_get(dev, "pcnoc-mport-clk");
	if (IS_ERR(drvdata->pcnoc_mport_clk)) {
		dev_err(&pdev->dev, "error getting pcnoc-mport-clk: %ld\n",
			PTR_ERR(drvdata->pcnoc_mport_clk));
		return PTR_ERR(drvdata->pcnoc_mport_clk);
	}

	ret = clk_prepare_enable(drvdata->pcnoc_mport_clk);
	if (ret) {
		dev_err(&pdev->dev, "Error enabling pcnoc-mport-clk: %d\n",
			ret);
		return ret;
	}

	drvdata->pcnoc_sway_clk = devm_clk_get(dev, "pcnoc-sway-clk");
	if (IS_ERR(drvdata->pcnoc_sway_clk)) {
		dev_err(&pdev->dev, "error getting pcnoc-sway-clk: %ld\n",
			PTR_ERR(drvdata->pcnoc_sway_clk));
		return PTR_ERR(drvdata->pcnoc_sway_clk);
	}

	ret = clk_prepare_enable(drvdata->pcnoc_sway_clk);
	if (ret) {
		dev_err(&pdev->dev, "Error enabling pcnoc_sway_clk: %d\n", ret);
		return ret;
	}

	return 0;
}