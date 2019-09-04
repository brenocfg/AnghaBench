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
struct stmmac_resources {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct plat_stmmacenet_data {void* stmmac_clk; void* pclk; } ;

/* Variables and functions */
 void* ERR_CAST (void*) ; 
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void *dwc_qos_probe(struct platform_device *pdev,
			   struct plat_stmmacenet_data *plat_dat,
			   struct stmmac_resources *stmmac_res)
{
	int err;

	plat_dat->stmmac_clk = devm_clk_get(&pdev->dev, "apb_pclk");
	if (IS_ERR(plat_dat->stmmac_clk)) {
		dev_err(&pdev->dev, "apb_pclk clock not found.\n");
		return ERR_CAST(plat_dat->stmmac_clk);
	}

	err = clk_prepare_enable(plat_dat->stmmac_clk);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to enable apb_pclk clock: %d\n",
			err);
		return ERR_PTR(err);
	}

	plat_dat->pclk = devm_clk_get(&pdev->dev, "phy_ref_clk");
	if (IS_ERR(plat_dat->pclk)) {
		dev_err(&pdev->dev, "phy_ref_clk clock not found.\n");
		err = PTR_ERR(plat_dat->pclk);
		goto disable;
	}

	err = clk_prepare_enable(plat_dat->pclk);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to enable phy_ref clock: %d\n",
			err);
		goto disable;
	}

	return NULL;

disable:
	clk_disable_unprepare(plat_dat->stmmac_clk);
	return ERR_PTR(err);
}