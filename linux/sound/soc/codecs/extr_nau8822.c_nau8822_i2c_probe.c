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
struct nau8822 {int /*<<< orphan*/  regmap; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAU8822_REG_RESET ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct nau8822* dev_get_platdata (struct device*) ; 
 struct nau8822* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nau8822*) ; 
 int /*<<< orphan*/  nau8822_dai ; 
 int /*<<< orphan*/  nau8822_regmap_config ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_component_dev_nau8822 ; 

__attribute__((used)) static int nau8822_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct nau8822 *nau8822 = dev_get_platdata(dev);
	int ret;

	if (!nau8822) {
		nau8822 = devm_kzalloc(dev, sizeof(*nau8822), GFP_KERNEL);
		if (nau8822 == NULL)
			return -ENOMEM;
	}
	i2c_set_clientdata(i2c, nau8822);

	nau8822->regmap = devm_regmap_init_i2c(i2c, &nau8822_regmap_config);
	if (IS_ERR(nau8822->regmap)) {
		ret = PTR_ERR(nau8822->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}
	nau8822->dev = dev;

	/* Reset the codec */
	ret = regmap_write(nau8822->regmap, NAU8822_REG_RESET, 0x00);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(dev, &soc_component_dev_nau8822,
						&nau8822_dai, 1);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		return ret;
	}

	return 0;
}