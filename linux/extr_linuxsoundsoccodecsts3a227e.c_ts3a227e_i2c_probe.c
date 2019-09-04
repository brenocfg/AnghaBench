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
struct ts3a227e {int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ADC_COMPLETE_INT_DISABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTB_DISABLE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS3A227E_REG_ACCESSORY_STATUS ; 
 int /*<<< orphan*/  TS3A227E_REG_INTERRUPT_DISABLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct ts3a227e* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct ts3a227e*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ts3a227e*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ts3a227e_interrupt ; 
 int /*<<< orphan*/  ts3a227e_jack_report (struct ts3a227e*) ; 
 int /*<<< orphan*/  ts3a227e_new_jack_state (struct ts3a227e*,unsigned int) ; 
 int ts3a227e_parse_device_property (struct ts3a227e*,struct device*) ; 
 int /*<<< orphan*/  ts3a227e_regmap_config ; 
 int /*<<< orphan*/  ts3a227e_soc_driver ; 

__attribute__((used)) static int ts3a227e_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct ts3a227e *ts3a227e;
	struct device *dev = &i2c->dev;
	int ret;
	unsigned int acc_reg;

	ts3a227e = devm_kzalloc(&i2c->dev, sizeof(*ts3a227e), GFP_KERNEL);
	if (ts3a227e == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, ts3a227e);
	ts3a227e->dev = dev;
	ts3a227e->irq = i2c->irq;

	ts3a227e->regmap = devm_regmap_init_i2c(i2c, &ts3a227e_regmap_config);
	if (IS_ERR(ts3a227e->regmap))
		return PTR_ERR(ts3a227e->regmap);

	ret = ts3a227e_parse_device_property(ts3a227e, dev);
	if (ret) {
		dev_err(dev, "Failed to parse device property: %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(dev, i2c->irq, NULL, ts3a227e_interrupt,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"TS3A227E", ts3a227e);
	if (ret) {
		dev_err(dev, "Cannot request irq %d (%d)\n", i2c->irq, ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&i2c->dev, &ts3a227e_soc_driver,
					      NULL, 0);
	if (ret)
		return ret;

	/* Enable interrupts except for ADC complete. */
	regmap_update_bits(ts3a227e->regmap, TS3A227E_REG_INTERRUPT_DISABLE,
			   INTB_DISABLE | ADC_COMPLETE_INT_DISABLE,
			   ADC_COMPLETE_INT_DISABLE);

	/* Read jack status because chip might not trigger interrupt at boot. */
	regmap_read(ts3a227e->regmap, TS3A227E_REG_ACCESSORY_STATUS, &acc_reg);
	ts3a227e_new_jack_state(ts3a227e, acc_reg);
	ts3a227e_jack_report(ts3a227e);

	return 0;
}