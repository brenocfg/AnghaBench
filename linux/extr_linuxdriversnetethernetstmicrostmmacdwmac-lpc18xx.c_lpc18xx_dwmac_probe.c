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
typedef  int /*<<< orphan*/  u8 ;
struct stmmac_resources {int /*<<< orphan*/  mac; } ;
struct regmap {int has_gmac; scalar_t__ interface; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct plat_stmmacenet_data {int has_gmac; scalar_t__ interface; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  LPC18XX_CREG_CREG6 ; 
 int /*<<< orphan*/  LPC18XX_CREG_CREG6_ETHMODE_MASK ; 
 int /*<<< orphan*/  LPC18XX_CREG_CREG6_ETHMODE_MII ; 
 int /*<<< orphan*/  LPC18XX_CREG_CREG6_ETHMODE_RMII ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stmmac_dvr_probe (int /*<<< orphan*/ *,struct regmap*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct regmap* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct regmap*) ; 
 struct regmap* syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int lpc18xx_dwmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	struct regmap *reg;
	u8 ethmode;
	int ret;

	ret = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (ret)
		return ret;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	plat_dat->has_gmac = true;

	reg = syscon_regmap_lookup_by_compatible("nxp,lpc1850-creg");
	if (IS_ERR(reg)) {
		dev_err(&pdev->dev, "syscon lookup failed\n");
		ret = PTR_ERR(reg);
		goto err_remove_config_dt;
	}

	if (plat_dat->interface == PHY_INTERFACE_MODE_MII) {
		ethmode = LPC18XX_CREG_CREG6_ETHMODE_MII;
	} else if (plat_dat->interface == PHY_INTERFACE_MODE_RMII) {
		ethmode = LPC18XX_CREG_CREG6_ETHMODE_RMII;
	} else {
		dev_err(&pdev->dev, "Only MII and RMII mode supported\n");
		ret = -EINVAL;
		goto err_remove_config_dt;
	}

	regmap_update_bits(reg, LPC18XX_CREG_CREG6,
			   LPC18XX_CREG_CREG6_ETHMODE_MASK, ethmode);

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto err_remove_config_dt;

	return 0;

err_remove_config_dt:
	stmmac_remove_config_dt(pdev, plat_dat);

	return ret;
}