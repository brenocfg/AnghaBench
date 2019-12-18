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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct adau {void (* switch_mode ) (struct device*) ;int type; struct regmap* sigmadsp; struct regmap* regmap; struct regmap* mclk; int /*<<< orphan*/  pll_regs; int /*<<< orphan*/  clk_src; } ;
typedef  enum adau17x1_type { ____Placeholder_adau17x1_type } adau17x1_type ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_CLK_SRC_PLL_AUTO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 scalar_t__ adau17x1_has_safeload (struct adau*) ; 
 int /*<<< orphan*/  adau17x1_sigmadsp_ops ; 
 int adau_calc_pll_cfg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (struct regmap*) ; 
 int clk_prepare_enable (struct regmap*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct adau*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct regmap* devm_clk_get (struct device*,char*) ; 
 struct adau* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_sigmadsp_init_regmap (struct device*,struct regmap*,int /*<<< orphan*/ *,char const*) ; 

int adau17x1_probe(struct device *dev, struct regmap *regmap,
	enum adau17x1_type type, void (*switch_mode)(struct device *dev),
	const char *firmware_name)
{
	struct adau *adau;
	int ret;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	adau = devm_kzalloc(dev, sizeof(*adau), GFP_KERNEL);
	if (!adau)
		return -ENOMEM;

	adau->mclk = devm_clk_get(dev, "mclk");
	if (IS_ERR(adau->mclk)) {
		if (PTR_ERR(adau->mclk) != -ENOENT)
			return PTR_ERR(adau->mclk);
		/* Clock is optional (for the driver) */
		adau->mclk = NULL;
	} else if (adau->mclk) {
		adau->clk_src = ADAU17X1_CLK_SRC_PLL_AUTO;

		/*
		 * Any valid PLL output rate will work at this point, use one
		 * that is likely to be chosen later as well. The register will
		 * be written when the PLL is powered up for the first time.
		 */
		ret = adau_calc_pll_cfg(clk_get_rate(adau->mclk), 48000 * 1024,
				adau->pll_regs);
		if (ret < 0)
			return ret;

		ret = clk_prepare_enable(adau->mclk);
		if (ret)
			return ret;
	}

	adau->regmap = regmap;
	adau->switch_mode = switch_mode;
	adau->type = type;

	dev_set_drvdata(dev, adau);

	if (firmware_name) {
		if (adau17x1_has_safeload(adau)) {
			adau->sigmadsp = devm_sigmadsp_init_regmap(dev, regmap,
				&adau17x1_sigmadsp_ops, firmware_name);
		} else {
			adau->sigmadsp = devm_sigmadsp_init_regmap(dev, regmap,
				NULL, firmware_name);
		}
		if (IS_ERR(adau->sigmadsp)) {
			dev_warn(dev, "Could not find firmware file: %ld\n",
				PTR_ERR(adau->sigmadsp));
			adau->sigmadsp = NULL;
		}
	}

	if (switch_mode)
		switch_mode(dev);

	return 0;
}