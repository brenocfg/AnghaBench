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
typedef  int u32 ;
struct stm32_iwdg {void* clk_lsi; int /*<<< orphan*/  rate; void* clk_pclk; scalar_t__ has_pclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int stm32_iwdg_clk_init(struct platform_device *pdev,
			       struct stm32_iwdg *wdt)
{
	u32 ret;

	wdt->clk_lsi = devm_clk_get(&pdev->dev, "lsi");
	if (IS_ERR(wdt->clk_lsi)) {
		dev_err(&pdev->dev, "Unable to get lsi clock\n");
		return PTR_ERR(wdt->clk_lsi);
	}

	/* optional peripheral clock */
	if (wdt->has_pclk) {
		wdt->clk_pclk = devm_clk_get(&pdev->dev, "pclk");
		if (IS_ERR(wdt->clk_pclk)) {
			dev_err(&pdev->dev, "Unable to get pclk clock\n");
			return PTR_ERR(wdt->clk_pclk);
		}

		ret = clk_prepare_enable(wdt->clk_pclk);
		if (ret) {
			dev_err(&pdev->dev, "Unable to prepare pclk clock\n");
			return ret;
		}
	}

	ret = clk_prepare_enable(wdt->clk_lsi);
	if (ret) {
		dev_err(&pdev->dev, "Unable to prepare lsi clock\n");
		clk_disable_unprepare(wdt->clk_pclk);
		return ret;
	}

	wdt->rate = clk_get_rate(wdt->clk_lsi);

	return 0;
}