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
struct nau8540 {int /*<<< orphan*/  regmap; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAU8540_REG_I2C_DEVICE_ID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct nau8540* dev_get_platdata (struct device*) ; 
 struct nau8540* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nau8540*) ; 
 int /*<<< orphan*/  nau8540_component_driver ; 
 int /*<<< orphan*/  nau8540_dai ; 
 int /*<<< orphan*/  nau8540_init_regs (struct nau8540*) ; 
 int /*<<< orphan*/  nau8540_regmap_config ; 
 int /*<<< orphan*/  nau8540_reset_chip (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int nau8540_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct nau8540 *nau8540 = dev_get_platdata(dev);
	int ret, value;

	if (!nau8540) {
		nau8540 = devm_kzalloc(dev, sizeof(*nau8540), GFP_KERNEL);
		if (!nau8540)
			return -ENOMEM;
	}
	i2c_set_clientdata(i2c, nau8540);

	nau8540->regmap = devm_regmap_init_i2c(i2c, &nau8540_regmap_config);
	if (IS_ERR(nau8540->regmap))
		return PTR_ERR(nau8540->regmap);
	ret = regmap_read(nau8540->regmap, NAU8540_REG_I2C_DEVICE_ID, &value);
	if (ret < 0) {
		dev_err(dev, "Failed to read device id from the NAU85L40: %d\n",
			ret);
		return ret;
	}

	nau8540->dev = dev;
	nau8540_reset_chip(nau8540->regmap);
	nau8540_init_regs(nau8540);

	return devm_snd_soc_register_component(dev,
		&nau8540_component_driver, &nau8540_dai, 1);
}