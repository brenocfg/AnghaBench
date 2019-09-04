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
struct max98373_priv {int interleave_mode; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX98373_R21FF_REV_ID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 struct max98373_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max98373_priv*) ; 
 int /*<<< orphan*/  max98373_dai ; 
 int /*<<< orphan*/  max98373_regmap ; 
 int /*<<< orphan*/  max98373_slot_config (struct i2c_client*,struct max98373_priv*) ; 
 int regmap_read (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  soc_codec_dev_max98373 ; 

__attribute__((used)) static int max98373_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{

	int ret = 0;
	int reg = 0;
	struct max98373_priv *max98373 = NULL;

	max98373 = devm_kzalloc(&i2c->dev, sizeof(*max98373), GFP_KERNEL);

	if (!max98373) {
		ret = -ENOMEM;
		return ret;
	}
	i2c_set_clientdata(i2c, max98373);

	/* update interleave mode info */
	if (device_property_read_bool(&i2c->dev, "maxim,interleave_mode"))
		max98373->interleave_mode = 1;
	else
		max98373->interleave_mode = 0;


	/* regmap initialization */
	max98373->regmap
		= devm_regmap_init_i2c(i2c, &max98373_regmap);
	if (IS_ERR(max98373->regmap)) {
		ret = PTR_ERR(max98373->regmap);
		dev_err(&i2c->dev,
			"Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	/* Check Revision ID */
	ret = regmap_read(max98373->regmap,
		MAX98373_R21FF_REV_ID, &reg);
	if (ret < 0) {
		dev_err(&i2c->dev,
			"Failed to read: 0x%02X\n", MAX98373_R21FF_REV_ID);
		return ret;
	}
	dev_info(&i2c->dev, "MAX98373 revisionID: 0x%02X\n", reg);

	/* voltage/current slot configuration */
	max98373_slot_config(i2c, max98373);

	/* codec registeration */
	ret = devm_snd_soc_register_component(&i2c->dev, &soc_codec_dev_max98373,
		max98373_dai, ARRAY_SIZE(max98373_dai));
	if (ret < 0)
		dev_err(&i2c->dev, "Failed to register codec: %d\n", ret);

	return ret;
}