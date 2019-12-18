#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct of_device_id {TYPE_2__* data; } ;
struct device {int dummy; } ;
struct cs42xx8_priv {TYPE_3__* supplies; struct regmap* regmap; TYPE_2__* drvdata; struct regmap* clk; int /*<<< orphan*/  sysclk; struct regmap* gpiod_reset; } ;
struct TYPE_9__ {int channels_max; } ;
struct TYPE_12__ {TYPE_1__ capture; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  supply; } ;
struct TYPE_10__ {int num_adcs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  CS42XX8_CHIPID ; 
 int CS42XX8_CHIPID_CHIP_ID_MASK ; 
 int CS42XX8_CHIPID_REV_ID_MASK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_get_rate (struct regmap*) ; 
 TYPE_5__ cs42xx8_dai ; 
 int /*<<< orphan*/  cs42xx8_driver ; 
 int /*<<< orphan*/  cs42xx8_of_match ; 
 int /*<<< orphan*/ * cs42xx8_supply_names ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct cs42xx8_priv*) ; 
 struct regmap* devm_clk_get (struct device*,char*) ; 
 struct regmap* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct cs42xx8_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_3__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct regmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  regcache_cache_only (struct regmap*,int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_3__*) ; 
 int regulator_bulk_enable (int,TYPE_3__*) ; 

int cs42xx8_probe(struct device *dev, struct regmap *regmap)
{
	const struct of_device_id *of_id;
	struct cs42xx8_priv *cs42xx8;
	int ret, val, i;

	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(dev, "failed to allocate regmap: %d\n", ret);
		return ret;
	}

	cs42xx8 = devm_kzalloc(dev, sizeof(*cs42xx8), GFP_KERNEL);
	if (cs42xx8 == NULL)
		return -ENOMEM;

	cs42xx8->regmap = regmap;
	dev_set_drvdata(dev, cs42xx8);

	of_id = of_match_device(cs42xx8_of_match, dev);
	if (of_id)
		cs42xx8->drvdata = of_id->data;

	if (!cs42xx8->drvdata) {
		dev_err(dev, "failed to find driver data\n");
		return -EINVAL;
	}

	cs42xx8->gpiod_reset = devm_gpiod_get_optional(dev, "reset",
							GPIOD_OUT_HIGH);
	if (IS_ERR(cs42xx8->gpiod_reset))
		return PTR_ERR(cs42xx8->gpiod_reset);

	gpiod_set_value_cansleep(cs42xx8->gpiod_reset, 0);

	cs42xx8->clk = devm_clk_get(dev, "mclk");
	if (IS_ERR(cs42xx8->clk)) {
		dev_err(dev, "failed to get the clock: %ld\n",
				PTR_ERR(cs42xx8->clk));
		return -EINVAL;
	}

	cs42xx8->sysclk = clk_get_rate(cs42xx8->clk);

	for (i = 0; i < ARRAY_SIZE(cs42xx8->supplies); i++)
		cs42xx8->supplies[i].supply = cs42xx8_supply_names[i];

	ret = devm_regulator_bulk_get(dev,
			ARRAY_SIZE(cs42xx8->supplies), cs42xx8->supplies);
	if (ret) {
		dev_err(dev, "failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(cs42xx8->supplies),
				    cs42xx8->supplies);
	if (ret) {
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		return ret;
	}

	/* Make sure hardware reset done */
	msleep(5);

	/* Validate the chip ID */
	ret = regmap_read(cs42xx8->regmap, CS42XX8_CHIPID, &val);
	if (ret < 0) {
		dev_err(dev, "failed to get device ID, ret = %d", ret);
		goto err_enable;
	}

	/* The top four bits of the chip ID should be 0000 */
	if (((val & CS42XX8_CHIPID_CHIP_ID_MASK) >> 4) != 0x00) {
		dev_err(dev, "unmatched chip ID: %d\n",
			(val & CS42XX8_CHIPID_CHIP_ID_MASK) >> 4);
		ret = -EINVAL;
		goto err_enable;
	}

	dev_info(dev, "found device, revision %X\n",
			val & CS42XX8_CHIPID_REV_ID_MASK);

	cs42xx8_dai.name = cs42xx8->drvdata->name;

	/* Each adc supports stereo input */
	cs42xx8_dai.capture.channels_max = cs42xx8->drvdata->num_adcs * 2;

	ret = devm_snd_soc_register_component(dev, &cs42xx8_driver, &cs42xx8_dai, 1);
	if (ret) {
		dev_err(dev, "failed to register component:%d\n", ret);
		goto err_enable;
	}

	regcache_cache_only(cs42xx8->regmap, true);

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(cs42xx8->supplies),
			       cs42xx8->supplies);

	return ret;
}