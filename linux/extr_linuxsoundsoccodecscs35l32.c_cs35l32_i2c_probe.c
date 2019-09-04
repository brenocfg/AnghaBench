#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_17__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_4__ dev; } ;
struct cs35l32_platform_data {int boost_mng; int sdout_share; int sdout_datacfg; int batt_recov; int batt_thresh; } ;
struct cs35l32_private {TYPE_1__* supplies; int /*<<< orphan*/  regmap; struct cs35l32_platform_data pdata; int /*<<< orphan*/  reset_gpio; } ;
struct TYPE_16__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CS35L32_ADSP_CTL ; 
 int CS35L32_ADSP_DATACFG_MASK ; 
 int CS35L32_ADSP_SHARE_MASK ; 
 int /*<<< orphan*/  CS35L32_AUDIO_LED_MNGR ; 
 int CS35L32_BATT_REC_MASK ; 
 int /*<<< orphan*/  CS35L32_BATT_THRESHOLD ; 
 int CS35L32_BATT_THRESH_MASK ; 
 int CS35L32_BOOST_MASK ; 
 unsigned int CS35L32_CHIP_ID ; 
 int /*<<< orphan*/  CS35L32_DEVID_AB ; 
 int /*<<< orphan*/  CS35L32_DEVID_CD ; 
 int /*<<< orphan*/  CS35L32_DEVID_E ; 
 int /*<<< orphan*/  CS35L32_INT_STATUS_1 ; 
 int CS35L32_PDN_AMP ; 
 int /*<<< orphan*/  CS35L32_PWRCTL1 ; 
 int /*<<< orphan*/  CS35L32_REV_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* cs35l32_dai ; 
 int cs35l32_handle_of_data (struct i2c_client*,struct cs35l32_platform_data*) ; 
 TYPE_1__* cs35l32_monitor_patch ; 
 int /*<<< orphan*/  cs35l32_regmap ; 
 int /*<<< orphan*/ * cs35l32_supply_names ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct cs35l32_platform_data* dev_get_platdata (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,unsigned int) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (TYPE_4__*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (TYPE_4__*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cs35l32_private*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  soc_component_dev_cs35l32 ; 

__attribute__((used)) static int cs35l32_i2c_probe(struct i2c_client *i2c_client,
				       const struct i2c_device_id *id)
{
	struct cs35l32_private *cs35l32;
	struct cs35l32_platform_data *pdata =
		dev_get_platdata(&i2c_client->dev);
	int ret, i;
	unsigned int devid = 0;
	unsigned int reg;

	cs35l32 = devm_kzalloc(&i2c_client->dev, sizeof(*cs35l32), GFP_KERNEL);
	if (!cs35l32)
		return -ENOMEM;

	i2c_set_clientdata(i2c_client, cs35l32);

	cs35l32->regmap = devm_regmap_init_i2c(i2c_client, &cs35l32_regmap);
	if (IS_ERR(cs35l32->regmap)) {
		ret = PTR_ERR(cs35l32->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	if (pdata) {
		cs35l32->pdata = *pdata;
	} else {
		pdata = devm_kzalloc(&i2c_client->dev, sizeof(*pdata),
				     GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;

		if (i2c_client->dev.of_node) {
			ret = cs35l32_handle_of_data(i2c_client,
						     &cs35l32->pdata);
			if (ret != 0)
				return ret;
		}
	}

	for (i = 0; i < ARRAY_SIZE(cs35l32->supplies); i++)
		cs35l32->supplies[i].supply = cs35l32_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c_client->dev,
				      ARRAY_SIZE(cs35l32->supplies),
				      cs35l32->supplies);
	if (ret != 0) {
		dev_err(&i2c_client->dev,
			"Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(cs35l32->supplies),
				    cs35l32->supplies);
	if (ret != 0) {
		dev_err(&i2c_client->dev,
			"Failed to enable supplies: %d\n", ret);
		return ret;
	}

	/* Reset the Device */
	cs35l32->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
		"reset", GPIOD_OUT_LOW);
	if (IS_ERR(cs35l32->reset_gpio))
		return PTR_ERR(cs35l32->reset_gpio);

	gpiod_set_value_cansleep(cs35l32->reset_gpio, 1);

	/* initialize codec */
	ret = regmap_read(cs35l32->regmap, CS35L32_DEVID_AB, &reg);
	devid = (reg & 0xFF) << 12;

	ret = regmap_read(cs35l32->regmap, CS35L32_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;

	ret = regmap_read(cs35l32->regmap, CS35L32_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	if (devid != CS35L32_CHIP_ID) {
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS35L32 Device ID (%X). Expected %X\n",
			devid, CS35L32_CHIP_ID);
		return ret;
	}

	ret = regmap_read(cs35l32->regmap, CS35L32_REV_ID, &reg);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		return ret;
	}

	ret = regmap_register_patch(cs35l32->regmap, cs35l32_monitor_patch,
				    ARRAY_SIZE(cs35l32_monitor_patch));
	if (ret < 0) {
		dev_err(&i2c_client->dev, "Failed to apply errata patch\n");
		return ret;
	}

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS35L32, Revision: %02X\n", reg & 0xFF);

	/* Setup VBOOST Management */
	if (cs35l32->pdata.boost_mng)
		regmap_update_bits(cs35l32->regmap, CS35L32_AUDIO_LED_MNGR,
				   CS35L32_BOOST_MASK,
				cs35l32->pdata.boost_mng);

	/* Setup ADSP Format Config */
	if (cs35l32->pdata.sdout_share)
		regmap_update_bits(cs35l32->regmap, CS35L32_ADSP_CTL,
				    CS35L32_ADSP_SHARE_MASK,
				cs35l32->pdata.sdout_share << 3);

	/* Setup ADSP Data Configuration */
	if (cs35l32->pdata.sdout_datacfg)
		regmap_update_bits(cs35l32->regmap, CS35L32_ADSP_CTL,
				   CS35L32_ADSP_DATACFG_MASK,
				cs35l32->pdata.sdout_datacfg << 4);

	/* Setup Low Battery Recovery  */
	if (cs35l32->pdata.batt_recov)
		regmap_update_bits(cs35l32->regmap, CS35L32_BATT_THRESHOLD,
				   CS35L32_BATT_REC_MASK,
				cs35l32->pdata.batt_recov << 1);

	/* Setup Low Battery Threshold */
	if (cs35l32->pdata.batt_thresh)
		regmap_update_bits(cs35l32->regmap, CS35L32_BATT_THRESHOLD,
				   CS35L32_BATT_THRESH_MASK,
				cs35l32->pdata.batt_thresh << 4);

	/* Power down the AMP */
	regmap_update_bits(cs35l32->regmap, CS35L32_PWRCTL1, CS35L32_PDN_AMP,
			    CS35L32_PDN_AMP);

	/* Clear MCLK Error Bit since we don't have the clock yet */
	ret = regmap_read(cs35l32->regmap, CS35L32_INT_STATUS_1, &reg);

	ret = devm_snd_soc_register_component(&i2c_client->dev,
			&soc_component_dev_cs35l32, cs35l32_dai,
			ARRAY_SIZE(cs35l32_dai));
	if (ret < 0)
		goto err_disable;

	return 0;

err_disable:
	regulator_bulk_disable(ARRAY_SIZE(cs35l32->supplies),
			       cs35l32->supplies);
	return ret;
}