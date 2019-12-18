#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rt5682_platform_data {int dmic1_data_pin; int dmic1_clk_pin; int /*<<< orphan*/  ldo1_en; } ;
struct rt5682_priv {int /*<<< orphan*/  jd_check_work; int /*<<< orphan*/  jack_detect_work; int /*<<< orphan*/  regmap; struct rt5682_platform_data pdata; int /*<<< orphan*/  calibrate_mutex; TYPE_1__* supplies; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct TYPE_8__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int DEVICE_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5682_BIAS_CUR_CTRL_8 ; 
 int /*<<< orphan*/  RT5682_CHARGE_PUMP_1 ; 
 int RT5682_CP_CLK_HP_300KHZ ; 
 int RT5682_CP_CLK_HP_MASK ; 
 int /*<<< orphan*/  RT5682_DEPOP_1 ; 
 int /*<<< orphan*/  RT5682_DEVICE_ID ; 
#define  RT5682_DMIC1_CLK_GPIO1 131 
#define  RT5682_DMIC1_CLK_GPIO3 130 
#define  RT5682_DMIC1_DATA_GPIO2 129 
#define  RT5682_DMIC1_DATA_GPIO5 128 
 int RT5682_DMIC1_NULL ; 
 int RT5682_DMIC_1_DP_GPIO2 ; 
 int RT5682_DMIC_1_DP_GPIO5 ; 
 int RT5682_DMIC_1_DP_MASK ; 
 int /*<<< orphan*/  RT5682_DMIC_CTRL_1 ; 
 int RT5682_GP1_PIN_DMIC_CLK ; 
 int RT5682_GP1_PIN_MASK ; 
 int RT5682_GP2_PIN_DMIC_SDA ; 
 int RT5682_GP2_PIN_MASK ; 
 int RT5682_GP3_PIN_DMIC_CLK ; 
 int RT5682_GP3_PIN_MASK ; 
 int RT5682_GP4_PIN_ADCDAT1 ; 
 int RT5682_GP4_PIN_MASK ; 
 int RT5682_GP5_PIN_DACDAT1 ; 
 int RT5682_GP5_PIN_DMIC_SDA ; 
 int RT5682_GP5_PIN_MASK ; 
 int /*<<< orphan*/  RT5682_GPIO_CTRL_1 ; 
 int RT5682_HPA_CP_BIAS_3UA ; 
 int RT5682_HPA_CP_BIAS_CTRL_MASK ; 
 int RT5682_HP_DRIVER_5X ; 
 int RT5682_HP_DRIVER_MASK ; 
 int /*<<< orphan*/  RT5682_I2C_MODE ; 
 int RT5682_LDO1_DVO_12 ; 
 int RT5682_LDO1_DVO_MASK ; 
 int /*<<< orphan*/  RT5682_MICBIAS_2 ; 
 int /*<<< orphan*/  RT5682_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5682_TEST_MODE_CTRL_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct rt5682_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rt5682_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct rt5682_priv*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5682_priv*) ; 
 struct rt5682_platform_data i2s_default_platform_data ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* patch_list ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int regmap_multi_reg_write (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  rt5682_calibrate (struct rt5682_priv*) ; 
 TYPE_1__* rt5682_dai ; 
 int /*<<< orphan*/  rt5682_irq ; 
 int /*<<< orphan*/  rt5682_jack_detect_handler ; 
 int /*<<< orphan*/  rt5682_jd_check_handler ; 
 int /*<<< orphan*/  rt5682_parse_dt (struct rt5682_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5682_regmap ; 
 int /*<<< orphan*/  rt5682_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rt5682_supply_names ; 
 int /*<<< orphan*/  soc_component_dev_rt5682 ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5682_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt5682_platform_data *pdata = dev_get_platdata(&i2c->dev);
	struct rt5682_priv *rt5682;
	int i, ret;
	unsigned int val;

	rt5682 = devm_kzalloc(&i2c->dev, sizeof(struct rt5682_priv),
		GFP_KERNEL);

	if (rt5682 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt5682);

	rt5682->pdata = i2s_default_platform_data;

	if (pdata)
		rt5682->pdata = *pdata;
	else
		rt5682_parse_dt(rt5682, &i2c->dev);

	rt5682->regmap = devm_regmap_init_i2c(i2c, &rt5682_regmap);
	if (IS_ERR(rt5682->regmap)) {
		ret = PTR_ERR(rt5682->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(rt5682->supplies); i++)
		rt5682->supplies[i].supply = rt5682_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(rt5682->supplies),
				      rt5682->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(rt5682->supplies),
				    rt5682->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	if (gpio_is_valid(rt5682->pdata.ldo1_en)) {
		if (devm_gpio_request_one(&i2c->dev, rt5682->pdata.ldo1_en,
					  GPIOF_OUT_INIT_HIGH, "rt5682"))
			dev_err(&i2c->dev, "Fail gpio_request gpio_ldo\n");
	}

	/* Sleep for 300 ms miniumum */
	usleep_range(300000, 350000);

	regmap_write(rt5682->regmap, RT5682_I2C_MODE, 0x1);
	usleep_range(10000, 15000);

	regmap_read(rt5682->regmap, RT5682_DEVICE_ID, &val);
	if (val != DEVICE_ID) {
		pr_err("Device with ID register %x is not rt5682\n", val);
		return -ENODEV;
	}

	rt5682_reset(rt5682->regmap);

	mutex_init(&rt5682->calibrate_mutex);
	rt5682_calibrate(rt5682);

	ret = regmap_multi_reg_write(rt5682->regmap, patch_list,
				    ARRAY_SIZE(patch_list));
	if (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_write(rt5682->regmap, RT5682_DEPOP_1, 0x0000);

	/* DMIC pin*/
	if (rt5682->pdata.dmic1_data_pin != RT5682_DMIC1_NULL) {
		switch (rt5682->pdata.dmic1_data_pin) {
		case RT5682_DMIC1_DATA_GPIO2: /* share with LRCK2 */
			regmap_update_bits(rt5682->regmap, RT5682_DMIC_CTRL_1,
				RT5682_DMIC_1_DP_MASK, RT5682_DMIC_1_DP_GPIO2);
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP2_PIN_MASK, RT5682_GP2_PIN_DMIC_SDA);
			break;

		case RT5682_DMIC1_DATA_GPIO5: /* share with DACDAT1 */
			regmap_update_bits(rt5682->regmap, RT5682_DMIC_CTRL_1,
				RT5682_DMIC_1_DP_MASK, RT5682_DMIC_1_DP_GPIO5);
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP5_PIN_MASK, RT5682_GP5_PIN_DMIC_SDA);
			break;

		default:
			dev_warn(&i2c->dev, "invalid DMIC_DAT pin\n");
			break;
		}

		switch (rt5682->pdata.dmic1_clk_pin) {
		case RT5682_DMIC1_CLK_GPIO1: /* share with IRQ */
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP1_PIN_MASK, RT5682_GP1_PIN_DMIC_CLK);
			break;

		case RT5682_DMIC1_CLK_GPIO3: /* share with BCLK2 */
			regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
				RT5682_GP3_PIN_MASK, RT5682_GP3_PIN_DMIC_CLK);
			break;

		default:
			dev_warn(&i2c->dev, "invalid DMIC_CLK pin\n");
			break;
		}
	}

	regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
			RT5682_LDO1_DVO_MASK | RT5682_HP_DRIVER_MASK,
			RT5682_LDO1_DVO_12 | RT5682_HP_DRIVER_5X);
	regmap_write(rt5682->regmap, RT5682_MICBIAS_2, 0x0380);
	regmap_update_bits(rt5682->regmap, RT5682_GPIO_CTRL_1,
			RT5682_GP4_PIN_MASK | RT5682_GP5_PIN_MASK,
			RT5682_GP4_PIN_ADCDAT1 | RT5682_GP5_PIN_DACDAT1);
	regmap_write(rt5682->regmap, RT5682_TEST_MODE_CTRL_1, 0x0000);
	regmap_update_bits(rt5682->regmap, RT5682_BIAS_CUR_CTRL_8,
			RT5682_HPA_CP_BIAS_CTRL_MASK, RT5682_HPA_CP_BIAS_3UA);
	regmap_update_bits(rt5682->regmap, RT5682_CHARGE_PUMP_1,
			RT5682_CP_CLK_HP_MASK, RT5682_CP_CLK_HP_300KHZ);

	INIT_DELAYED_WORK(&rt5682->jack_detect_work,
				rt5682_jack_detect_handler);
	INIT_DELAYED_WORK(&rt5682->jd_check_work,
				rt5682_jd_check_handler);


	if (i2c->irq) {
		ret = devm_request_threaded_irq(&i2c->dev, i2c->irq, NULL,
			rt5682_irq, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5682", rt5682);
		if (ret)
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);

	}

	return devm_snd_soc_register_component(&i2c->dev,
					&soc_component_dev_rt5682,
					rt5682_dai, ARRAY_SIZE(rt5682_dai));
}