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
struct nau8825 {int xtalk_protect; int xtalk_baktab_initialized; int /*<<< orphan*/  regmap; int /*<<< orphan*/  xtalk_work; int /*<<< orphan*/  xtalk_sem; int /*<<< orphan*/  xtalk_state; scalar_t__ irq; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; scalar_t__ irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAU8825_REG_I2C_DEVICE_ID ; 
 int NAU8825_SOFTWARE_ID_MASK ; 
 int NAU8825_SOFTWARE_ID_NAU8825 ; 
 int /*<<< orphan*/  NAU8825_XTALK_DONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct nau8825* dev_get_platdata (struct device*) ; 
 struct nau8825* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_component_driver ; 
 int /*<<< orphan*/  nau8825_dai ; 
 int /*<<< orphan*/  nau8825_init_regs (struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_print_device_properties (struct nau8825*) ; 
 int nau8825_read_device_properties (struct device*,struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_regmap_config ; 
 int /*<<< orphan*/  nau8825_reset_chip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8825_setup_irq (struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_xtalk_work ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nau8825_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct nau8825 *nau8825 = dev_get_platdata(&i2c->dev);
	int ret, value;

	if (!nau8825) {
		nau8825 = devm_kzalloc(dev, sizeof(*nau8825), GFP_KERNEL);
		if (!nau8825)
			return -ENOMEM;
		ret = nau8825_read_device_properties(dev, nau8825);
		if (ret)
			return ret;
	}

	i2c_set_clientdata(i2c, nau8825);

	nau8825->regmap = devm_regmap_init_i2c(i2c, &nau8825_regmap_config);
	if (IS_ERR(nau8825->regmap))
		return PTR_ERR(nau8825->regmap);
	nau8825->dev = dev;
	nau8825->irq = i2c->irq;
	/* Initiate parameters, semaphore and work queue which are needed in
	 * cross talk suppression measurment function.
	 */
	nau8825->xtalk_state = NAU8825_XTALK_DONE;
	nau8825->xtalk_protect = false;
	nau8825->xtalk_baktab_initialized = false;
	sema_init(&nau8825->xtalk_sem, 1);
	INIT_WORK(&nau8825->xtalk_work, nau8825_xtalk_work);

	nau8825_print_device_properties(nau8825);

	nau8825_reset_chip(nau8825->regmap);
	ret = regmap_read(nau8825->regmap, NAU8825_REG_I2C_DEVICE_ID, &value);
	if (ret < 0) {
		dev_err(dev, "Failed to read device id from the NAU8825: %d\n",
			ret);
		return ret;
	}
	if ((value & NAU8825_SOFTWARE_ID_MASK) !=
			NAU8825_SOFTWARE_ID_NAU8825) {
		dev_err(dev, "Not a NAU8825 chip\n");
		return -ENODEV;
	}

	nau8825_init_regs(nau8825);

	if (i2c->irq)
		nau8825_setup_irq(nau8825);

	return devm_snd_soc_register_component(&i2c->dev,
		&nau8825_component_driver,
		&nau8825_dai, 1);
}