#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct adau1977 {int type; void (* switch_mode ) (struct device*) ;int max_master_fs; struct regmap* regmap; struct regmap* dvdd_reg; struct regmap* reset_gpio; struct regmap* avdd_reg; TYPE_1__ constraints; struct device* dev; } ;
typedef  enum adau1977_type { ____Placeholder_adau1977_type } adau1977_type ;

/* Variables and functions */
 int ADAU1977 ; 
 scalar_t__ ADAU1977_BLOCK_POWER_SAI_LDO_EN ; 
 int /*<<< orphan*/  ADAU1977_REG_BLOCK_POWER_SAI ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  adau1977_component_driver ; 
 int /*<<< orphan*/  adau1977_dai ; 
 int adau1977_power_disable (struct adau1977*) ; 
 int adau1977_power_enable (struct adau1977*) ; 
 int /*<<< orphan*/  adau1977_rates ; 
 int adau1977_setup_micbias (struct adau1977*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct adau1977*) ; 
 struct regmap* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct adau1977* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regulator_get (struct device*,char*) ; 
 struct regmap* devm_regulator_get_optional (struct device*,char*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,int) ; 

int adau1977_probe(struct device *dev, struct regmap *regmap,
	enum adau1977_type type, void (*switch_mode)(struct device *dev))
{
	unsigned int power_off_mask;
	struct adau1977 *adau1977;
	int ret;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	adau1977 = devm_kzalloc(dev, sizeof(*adau1977), GFP_KERNEL);
	if (adau1977 == NULL)
		return -ENOMEM;

	adau1977->dev = dev;
	adau1977->type = type;
	adau1977->regmap = regmap;
	adau1977->switch_mode = switch_mode;
	adau1977->max_master_fs = 192000;

	adau1977->constraints.list = adau1977_rates;
	adau1977->constraints.count = ARRAY_SIZE(adau1977_rates);

	adau1977->avdd_reg = devm_regulator_get(dev, "AVDD");
	if (IS_ERR(adau1977->avdd_reg))
		return PTR_ERR(adau1977->avdd_reg);

	adau1977->dvdd_reg = devm_regulator_get_optional(dev, "DVDD");
	if (IS_ERR(adau1977->dvdd_reg)) {
		if (PTR_ERR(adau1977->dvdd_reg) != -ENODEV)
			return PTR_ERR(adau1977->dvdd_reg);
		adau1977->dvdd_reg = NULL;
	}

	adau1977->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						       GPIOD_OUT_LOW);
	if (IS_ERR(adau1977->reset_gpio))
		return PTR_ERR(adau1977->reset_gpio);

	dev_set_drvdata(dev, adau1977);

	if (adau1977->reset_gpio)
		ndelay(100);

	ret = adau1977_power_enable(adau1977);
	if (ret)
		return ret;

	if (type == ADAU1977) {
		ret = adau1977_setup_micbias(adau1977);
		if (ret)
			goto err_poweroff;
	}

	if (adau1977->dvdd_reg)
		power_off_mask = ~0;
	else
		power_off_mask = (unsigned int)~ADAU1977_BLOCK_POWER_SAI_LDO_EN;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_BLOCK_POWER_SAI,
				power_off_mask, 0x00);
	if (ret)
		goto err_poweroff;

	ret = adau1977_power_disable(adau1977);
	if (ret)
		return ret;

	return devm_snd_soc_register_component(dev, &adau1977_component_driver,
			&adau1977_dai, 1);

err_poweroff:
	adau1977_power_disable(adau1977);
	return ret;

}