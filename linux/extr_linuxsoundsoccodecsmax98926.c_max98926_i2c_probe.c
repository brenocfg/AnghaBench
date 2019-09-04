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
struct max98926_priv {int interleave_mode; int /*<<< orphan*/  regmap; scalar_t__ i_slot; scalar_t__ v_slot; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX98926_DAI_IMON_SLOT_1E_1F ; 
 scalar_t__ MAX98926_DAI_VMON_SLOT_1E_1F ; 
 int /*<<< orphan*/  MAX98926_VERSION ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 struct max98926_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max98926_priv*) ; 
 int /*<<< orphan*/  max98926_dai ; 
 int /*<<< orphan*/  max98926_regmap ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  soc_component_dev_max98926 ; 

__attribute__((used)) static int max98926_i2c_probe(struct i2c_client *i2c,
		const struct i2c_device_id *id)
{
	int ret, reg;
	u32 value;
	struct max98926_priv *max98926;

	max98926 = devm_kzalloc(&i2c->dev,
			sizeof(*max98926), GFP_KERNEL);
	if (!max98926)
		return -ENOMEM;

	i2c_set_clientdata(i2c, max98926);
	max98926->regmap = devm_regmap_init_i2c(i2c, &max98926_regmap);
	if (IS_ERR(max98926->regmap)) {
		ret = PTR_ERR(max98926->regmap);
		dev_err(&i2c->dev,
				"Failed to allocate regmap: %d\n", ret);
		goto err_out;
	}
	if (of_property_read_bool(i2c->dev.of_node, "interleave-mode"))
		max98926->interleave_mode = true;

	if (!of_property_read_u32(i2c->dev.of_node, "vmon-slot-no", &value)) {
		if (value > MAX98926_DAI_VMON_SLOT_1E_1F) {
			dev_err(&i2c->dev, "vmon slot number is wrong:\n");
			return -EINVAL;
		}
		max98926->v_slot = value;
	}
	if (!of_property_read_u32(i2c->dev.of_node, "imon-slot-no", &value)) {
		if (value > MAX98926_DAI_IMON_SLOT_1E_1F) {
			dev_err(&i2c->dev, "imon slot number is wrong:\n");
			return -EINVAL;
		}
		max98926->i_slot = value;
	}
	ret = regmap_read(max98926->regmap,
			MAX98926_VERSION, &reg);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to read: %x\n", reg);
		return ret;
	}

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_max98926,
			max98926_dai, ARRAY_SIZE(max98926_dai));
	if (ret < 0)
		dev_err(&i2c->dev,
				"Failed to register component: %d\n", ret);
	dev_info(&i2c->dev, "device version: %x\n", reg);
err_out:
	return ret;
}