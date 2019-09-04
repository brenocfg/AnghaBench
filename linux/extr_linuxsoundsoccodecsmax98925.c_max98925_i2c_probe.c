#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct max98925_priv {int /*<<< orphan*/  regmap; scalar_t__ i_slot; scalar_t__ v_slot; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ M98925_DAI_IMON_SLOT_1E_1F ; 
 scalar_t__ M98925_DAI_VMON_SLOT_1E_1F ; 
 int /*<<< orphan*/  MAX98925_REV_VERSION ; 
 int MAX98925_VERSION ; 
 int MAX98925_VERSION1 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 struct max98925_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max98925_priv*) ; 
 int /*<<< orphan*/  max98925_dai ; 
 int /*<<< orphan*/  max98925_regmap ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  soc_component_dev_max98925 ; 

__attribute__((used)) static int max98925_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	int ret, reg;
	u32 value;
	struct max98925_priv *max98925;

	max98925 = devm_kzalloc(&i2c->dev,
			sizeof(*max98925), GFP_KERNEL);
	if (!max98925)
		return -ENOMEM;

	i2c_set_clientdata(i2c, max98925);
	max98925->regmap = devm_regmap_init_i2c(i2c, &max98925_regmap);
	if (IS_ERR(max98925->regmap)) {
		ret = PTR_ERR(max98925->regmap);
		dev_err(&i2c->dev,
				"Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	if (!of_property_read_u32(i2c->dev.of_node, "vmon-slot-no", &value)) {
		if (value > M98925_DAI_VMON_SLOT_1E_1F) {
			dev_err(&i2c->dev, "vmon slot number is wrong:\n");
			return -EINVAL;
		}
		max98925->v_slot = value;
	}
	if (!of_property_read_u32(i2c->dev.of_node, "imon-slot-no", &value)) {
		if (value > M98925_DAI_IMON_SLOT_1E_1F) {
			dev_err(&i2c->dev, "imon slot number is wrong:\n");
			return -EINVAL;
		}
		max98925->i_slot = value;
	}

	ret = regmap_read(max98925->regmap, MAX98925_REV_VERSION, &reg);
	if (ret < 0) {
		dev_err(&i2c->dev, "Read revision failed\n");
		return ret;
	}

	if ((reg != MAX98925_VERSION) && (reg != MAX98925_VERSION1)) {
		ret = -ENODEV;
		dev_err(&i2c->dev, "Invalid revision (%d 0x%02X)\n",
			ret, reg);
		return ret;
	}

	dev_info(&i2c->dev, "device version 0x%02X\n", reg);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_max98925,
			max98925_dai, ARRAY_SIZE(max98925_dai));
	if (ret < 0)
		dev_err(&i2c->dev,
				"Failed to register component: %d\n", ret);
	return ret;
}