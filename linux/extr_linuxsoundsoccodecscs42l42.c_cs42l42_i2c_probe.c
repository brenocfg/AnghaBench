#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_14__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  irq; } ;
struct cs42l42_private {TYPE_1__* supplies; scalar_t__ regmap; scalar_t__ reset_gpio; } ;
struct TYPE_13__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CS42L42_ADC_PDN_MASK ; 
 int CS42L42_ADC_PDN_SHIFT ; 
 int CS42L42_ASP_DAI_PDN_MASK ; 
 int CS42L42_ASP_DAI_PDN_SHIFT ; 
 int CS42L42_ASP_DAO_PDN_MASK ; 
 int CS42L42_ASP_DAO_PDN_SHIFT ; 
 unsigned int CS42L42_CHIP_ID ; 
 int /*<<< orphan*/  CS42L42_DEVID_AB ; 
 int /*<<< orphan*/  CS42L42_DEVID_CD ; 
 int /*<<< orphan*/  CS42L42_DEVID_E ; 
 int CS42L42_EQ_PDN_MASK ; 
 int CS42L42_EQ_PDN_SHIFT ; 
 int CS42L42_HP_PDN_MASK ; 
 int CS42L42_HP_PDN_SHIFT ; 
 int CS42L42_MIXER_PDN_MASK ; 
 int CS42L42_MIXER_PDN_SHIFT ; 
 int CS42L42_PDN_ALL_MASK ; 
 int CS42L42_PDN_ALL_SHIFT ; 
 int /*<<< orphan*/  CS42L42_PWR_CTL1 ; 
 int /*<<< orphan*/  CS42L42_REVID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  cs42l42_dai ; 
 int cs42l42_handle_device_data (struct i2c_client*,struct cs42l42_private*) ; 
 int /*<<< orphan*/  cs42l42_irq_thread ; 
 int /*<<< orphan*/  cs42l42_regmap ; 
 int /*<<< orphan*/  cs42l42_set_interrupt_masks (struct cs42l42_private*) ; 
 int /*<<< orphan*/  cs42l42_setup_hs_type_detect (struct cs42l42_private*) ; 
 int /*<<< orphan*/ * cs42l42_supply_names ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,unsigned int) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct cs42l42_private* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (TYPE_3__*,int,TYPE_1__*) ; 
 int devm_request_threaded_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct cs42l42_private*) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cs42l42_private*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int regmap_read (scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  soc_component_dev_cs42l42 ; 

__attribute__((used)) static int cs42l42_i2c_probe(struct i2c_client *i2c_client,
				       const struct i2c_device_id *id)
{
	struct cs42l42_private *cs42l42;
	int ret, i;
	unsigned int devid = 0;
	unsigned int reg;

	cs42l42 = devm_kzalloc(&i2c_client->dev, sizeof(struct cs42l42_private),
			       GFP_KERNEL);
	if (!cs42l42)
		return -ENOMEM;

	i2c_set_clientdata(i2c_client, cs42l42);

	cs42l42->regmap = devm_regmap_init_i2c(i2c_client, &cs42l42_regmap);
	if (IS_ERR(cs42l42->regmap)) {
		ret = PTR_ERR(cs42l42->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(cs42l42->supplies); i++)
		cs42l42->supplies[i].supply = cs42l42_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c_client->dev,
				      ARRAY_SIZE(cs42l42->supplies),
				      cs42l42->supplies);
	if (ret != 0) {
		dev_err(&i2c_client->dev,
			"Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(cs42l42->supplies),
				    cs42l42->supplies);
	if (ret != 0) {
		dev_err(&i2c_client->dev,
			"Failed to enable supplies: %d\n", ret);
		return ret;
	}

	/* Reset the Device */
	cs42l42->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
		"reset", GPIOD_OUT_LOW);
	if (IS_ERR(cs42l42->reset_gpio))
		return PTR_ERR(cs42l42->reset_gpio);

	if (cs42l42->reset_gpio) {
		dev_dbg(&i2c_client->dev, "Found reset GPIO\n");
		gpiod_set_value_cansleep(cs42l42->reset_gpio, 1);
	}
	mdelay(3);

	/* Request IRQ */
	ret = devm_request_threaded_irq(&i2c_client->dev,
			i2c_client->irq,
			NULL, cs42l42_irq_thread,
			IRQF_ONESHOT | IRQF_TRIGGER_LOW,
			"cs42l42", cs42l42);

	if (ret != 0)
		dev_err(&i2c_client->dev,
			"Failed to request IRQ: %d\n", ret);

	/* initialize codec */
	ret = regmap_read(cs42l42->regmap, CS42L42_DEVID_AB, &reg);
	devid = (reg & 0xFF) << 12;

	ret = regmap_read(cs42l42->regmap, CS42L42_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;

	ret = regmap_read(cs42l42->regmap, CS42L42_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	if (devid != CS42L42_CHIP_ID) {
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS42L42 Device ID (%X). Expected %X\n",
			devid, CS42L42_CHIP_ID);
		return ret;
	}

	ret = regmap_read(cs42l42->regmap, CS42L42_REVID, &reg);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		return ret;
	}

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS42L42, Revision: %02X\n", reg & 0xFF);

	/* Power up the codec */
	regmap_update_bits(cs42l42->regmap, CS42L42_PWR_CTL1,
			CS42L42_ASP_DAO_PDN_MASK |
			CS42L42_ASP_DAI_PDN_MASK |
			CS42L42_MIXER_PDN_MASK |
			CS42L42_EQ_PDN_MASK |
			CS42L42_HP_PDN_MASK |
			CS42L42_ADC_PDN_MASK |
			CS42L42_PDN_ALL_MASK,
			(1 << CS42L42_ASP_DAO_PDN_SHIFT) |
			(1 << CS42L42_ASP_DAI_PDN_SHIFT) |
			(1 << CS42L42_MIXER_PDN_SHIFT) |
			(1 << CS42L42_EQ_PDN_SHIFT) |
			(1 << CS42L42_HP_PDN_SHIFT) |
			(1 << CS42L42_ADC_PDN_SHIFT) |
			(0 << CS42L42_PDN_ALL_SHIFT));

	if (i2c_client->dev.of_node) {
		ret = cs42l42_handle_device_data(i2c_client, cs42l42);
		if (ret != 0)
			return ret;
	}

	/* Setup headset detection */
	cs42l42_setup_hs_type_detect(cs42l42);

	/* Mask/Unmask Interrupts */
	cs42l42_set_interrupt_masks(cs42l42);

	/* Register codec for machine driver */
	ret = devm_snd_soc_register_component(&i2c_client->dev,
			&soc_component_dev_cs42l42, &cs42l42_dai, 1);
	if (ret < 0)
		goto err_disable;
	return 0;

err_disable:
	regulator_bulk_disable(ARRAY_SIZE(cs42l42->supplies),
				cs42l42->supplies);
	return ret;
}