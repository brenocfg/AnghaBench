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
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;
struct katana_codec_priv {struct regmap* regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 unsigned int KATANA_CODEC_CHIP_ID ; 
 int /*<<< orphan*/  KATANA_CODEC_CHIP_ID_REG ; 
 int /*<<< orphan*/  KATANA_CODEC_RESET ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct katana_codec_priv*) ; 
 struct katana_codec_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config*) ; 
 int /*<<< orphan*/  katana_codec_component_driver ; 
 int /*<<< orphan*/  katana_codec_dai ; 
 struct regmap_config katana_codec_regmap ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int allo_katana_component_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;
	struct regmap_config config = katana_codec_regmap;
	struct device *dev = &i2c->dev;
	struct katana_codec_priv *katana_codec;
	unsigned int chip_id = 0;
	int ret;

	regmap = devm_regmap_init_i2c(i2c, &config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	katana_codec = devm_kzalloc(dev, sizeof(struct katana_codec_priv),
					GFP_KERNEL);
	if (!katana_codec)
		return -ENOMEM;

	dev_set_drvdata(dev, katana_codec);
	katana_codec->regmap = regmap;

	ret = regmap_read(regmap, KATANA_CODEC_CHIP_ID_REG, &chip_id);
	if ((ret != 0) || (chip_id != KATANA_CODEC_CHIP_ID)) {
		dev_err(dev, "Failed to read Chip or wrong Chip id: %d\n", ret);
		return ret;
	}
	regmap_update_bits(regmap, KATANA_CODEC_RESET, 0x01, 0x01);
	msleep(10);

	ret = snd_soc_register_component(dev, &katana_codec_component_driver,
				    &katana_codec_dai, 1);
	if (ret != 0) {
		dev_err(dev, "failed to register codec: %d\n", ret);
		return ret;
	}

	return 0;
}