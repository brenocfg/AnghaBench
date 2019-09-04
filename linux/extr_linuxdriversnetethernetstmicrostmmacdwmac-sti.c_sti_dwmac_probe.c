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
struct stmmac_resources {int /*<<< orphan*/  mac; } ;
struct sti_dwmac_of_data {int /*<<< orphan*/  fix_retime_src; } ;
struct sti_dwmac {int /*<<< orphan*/  clk; int /*<<< orphan*/  fix_retime_src; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct plat_stmmacenet_data {int /*<<< orphan*/  fix_mac_speed; struct sti_dwmac* bsp_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct plat_stmmacenet_data*) ; 
 int PTR_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct sti_dwmac* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct sti_dwmac_of_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int sti_dwmac_parse_data (struct sti_dwmac*,struct platform_device*) ; 
 int sti_dwmac_set_mode (struct sti_dwmac*) ; 
 int stmmac_dvr_probe (int /*<<< orphan*/ *,struct plat_stmmacenet_data*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct plat_stmmacenet_data* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 

__attribute__((used)) static int sti_dwmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	const struct sti_dwmac_of_data *data;
	struct stmmac_resources stmmac_res;
	struct sti_dwmac *dwmac;
	int ret;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_err(&pdev->dev, "No OF match data provided\n");
		return -EINVAL;
	}

	ret = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (ret)
		return ret;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	dwmac = devm_kzalloc(&pdev->dev, sizeof(*dwmac), GFP_KERNEL);
	if (!dwmac) {
		ret = -ENOMEM;
		goto err_remove_config_dt;
	}

	ret = sti_dwmac_parse_data(dwmac, pdev);
	if (ret) {
		dev_err(&pdev->dev, "Unable to parse OF data\n");
		goto err_remove_config_dt;
	}

	dwmac->fix_retime_src = data->fix_retime_src;

	plat_dat->bsp_priv = dwmac;
	plat_dat->fix_mac_speed = data->fix_retime_src;

	ret = clk_prepare_enable(dwmac->clk);
	if (ret)
		goto err_remove_config_dt;

	ret = sti_dwmac_set_mode(dwmac);
	if (ret)
		goto disable_clk;

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto disable_clk;

	return 0;

disable_clk:
	clk_disable_unprepare(dwmac->clk);
err_remove_config_dt:
	stmmac_remove_config_dt(pdev, plat_dat);

	return ret;
}