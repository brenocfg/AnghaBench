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
struct tscs42xx {int sysclk_src_id; int /*<<< orphan*/  pll_lock; int /*<<< orphan*/  coeff_ram_lock; int /*<<< orphan*/  audio_params_lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/  sysclk; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RV_RESET_ENABLE ; 
 int /*<<< orphan*/  R_RESET ; 
 int TSCS42XX_PLL_SRC_CNT ; 
 int TSCS42XX_PLL_SRC_XTAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tscs42xx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tscs42xx*) ; 
 int /*<<< orphan*/  init_coeff_ram_cache (struct tscs42xx*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int part_is_valid (struct tscs42xx*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_codec_dev_tscs42xx ; 
 int /*<<< orphan*/ * src_names ; 
 int /*<<< orphan*/  tscs42xx_dai ; 
 int /*<<< orphan*/  tscs42xx_patch ; 
 int /*<<< orphan*/  tscs42xx_regmap ; 

__attribute__((used)) static int tscs42xx_i2c_probe(struct i2c_client *i2c,
		const struct i2c_device_id *id)
{
	struct tscs42xx *tscs42xx;
	int src;
	int ret;

	tscs42xx = devm_kzalloc(&i2c->dev, sizeof(*tscs42xx), GFP_KERNEL);
	if (!tscs42xx) {
		ret = -ENOMEM;
		dev_err(&i2c->dev,
			"Failed to allocate memory for data (%d)\n", ret);
		return ret;
	}
	i2c_set_clientdata(i2c, tscs42xx);

	for (src = TSCS42XX_PLL_SRC_XTAL; src < TSCS42XX_PLL_SRC_CNT; src++) {
		tscs42xx->sysclk = devm_clk_get(&i2c->dev, src_names[src]);
		if (!IS_ERR(tscs42xx->sysclk)) {
			break;
		} else if (PTR_ERR(tscs42xx->sysclk) != -ENOENT) {
			ret = PTR_ERR(tscs42xx->sysclk);
			dev_err(&i2c->dev, "Failed to get sysclk (%d)\n", ret);
			return ret;
		}
	}
	if (src == TSCS42XX_PLL_SRC_CNT) {
		ret = -EINVAL;
		dev_err(&i2c->dev, "Failed to get a valid clock name (%d)\n",
				ret);
		return ret;
	}
	tscs42xx->sysclk_src_id = src;

	tscs42xx->regmap = devm_regmap_init_i2c(i2c, &tscs42xx_regmap);
	if (IS_ERR(tscs42xx->regmap)) {
		ret = PTR_ERR(tscs42xx->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap (%d)\n", ret);
		return ret;
	}

	init_coeff_ram_cache(tscs42xx);

	ret = part_is_valid(tscs42xx);
	if (ret <= 0) {
		dev_err(&i2c->dev, "No valid part (%d)\n", ret);
		ret = -ENODEV;
		return ret;
	}

	ret = regmap_write(tscs42xx->regmap, R_RESET, RV_RESET_ENABLE);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to reset device (%d)\n", ret);
		return ret;
	}

	ret = regmap_register_patch(tscs42xx->regmap, tscs42xx_patch,
			ARRAY_SIZE(tscs42xx_patch));
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to apply patch (%d)\n", ret);
		return ret;
	}

	mutex_init(&tscs42xx->audio_params_lock);
	mutex_init(&tscs42xx->coeff_ram_lock);
	mutex_init(&tscs42xx->pll_lock);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_codec_dev_tscs42xx, &tscs42xx_dai, 1);
	if (ret) {
		dev_err(&i2c->dev, "Failed to register codec (%d)\n", ret);
		return ret;
	}

	return 0;
}