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
struct msm8916_wcd_digital_priv {void* mclk; void* ahbclk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int msm8916_wcd_digital_get_clks(struct platform_device *pdev,
					struct msm8916_wcd_digital_priv	*priv)
{
	struct device *dev = &pdev->dev;

	priv->ahbclk = devm_clk_get(dev, "ahbix-clk");
	if (IS_ERR(priv->ahbclk)) {
		dev_err(dev, "failed to get ahbix clk\n");
		return PTR_ERR(priv->ahbclk);
	}

	priv->mclk = devm_clk_get(dev, "mclk");
	if (IS_ERR(priv->mclk)) {
		dev_err(dev, "failed to get mclk\n");
		return PTR_ERR(priv->mclk);
	}

	return 0;
}