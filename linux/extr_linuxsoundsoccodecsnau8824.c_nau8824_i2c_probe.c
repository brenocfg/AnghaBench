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
struct nau8824 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  jd_sem; scalar_t__ irq; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {scalar_t__ irq; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAU8824_REG_I2C_DEVICE_ID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct nau8824* dev_get_platdata (struct device*) ; 
 struct nau8824* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nau8824*) ; 
 int /*<<< orphan*/  nau8824_component_driver ; 
 int /*<<< orphan*/  nau8824_dai ; 
 int /*<<< orphan*/  nau8824_init_regs (struct nau8824*) ; 
 int /*<<< orphan*/  nau8824_print_device_properties (struct nau8824*) ; 
 int nau8824_read_device_properties (struct device*,struct nau8824*) ; 
 int /*<<< orphan*/  nau8824_regmap_config ; 
 int /*<<< orphan*/  nau8824_reset_chip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8824_setup_irq (struct nau8824*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nau8824_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct nau8824 *nau8824 = dev_get_platdata(dev);
	int ret, value;

	if (!nau8824) {
		nau8824 = devm_kzalloc(dev, sizeof(*nau8824), GFP_KERNEL);
		if (!nau8824)
			return -ENOMEM;
		ret = nau8824_read_device_properties(dev, nau8824);
		if (ret)
			return ret;
	}
	i2c_set_clientdata(i2c, nau8824);

	nau8824->regmap = devm_regmap_init_i2c(i2c, &nau8824_regmap_config);
	if (IS_ERR(nau8824->regmap))
		return PTR_ERR(nau8824->regmap);
	nau8824->dev = dev;
	nau8824->irq = i2c->irq;
	sema_init(&nau8824->jd_sem, 1);

	nau8824_print_device_properties(nau8824);

	ret = regmap_read(nau8824->regmap, NAU8824_REG_I2C_DEVICE_ID, &value);
	if (ret < 0) {
		dev_err(dev, "Failed to read device id from the NAU8824: %d\n",
			ret);
		return ret;
	}
	nau8824_reset_chip(nau8824->regmap);
	nau8824_init_regs(nau8824);

	if (i2c->irq)
		nau8824_setup_irq(nau8824);

	return devm_snd_soc_register_component(dev,
		&nau8824_component_driver, &nau8824_dai, 1);
}