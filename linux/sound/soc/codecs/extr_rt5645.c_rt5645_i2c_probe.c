#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rt5645_platform_data {int jd_mode; int dmic1_data_pin; int dmic2_data_pin; scalar_t__ level_trigger_irq; scalar_t__ inv_jd1_1; scalar_t__ in2_diff; } ;
struct rt5645_priv {scalar_t__ codec_type; unsigned int v_id; TYPE_1__* supplies; struct i2c_client* i2c; int /*<<< orphan*/  rcclock_work; int /*<<< orphan*/  jack_detect_work; int /*<<< orphan*/  btn_check_timer; struct regmap* regmap; struct rt5645_platform_data pdata; struct regmap* gpiod_hp_det; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct dmi_system_id {struct rt5645_platform_data* driver_data; int /*<<< orphan*/  ident; } ;
struct TYPE_10__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CODEC_TYPE_RT5645 ; 
 scalar_t__ CODEC_TYPE_RT5650 ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int QUIRK_DMIC1_DATA_PIN (int) ; 
 int QUIRK_DMIC2_DATA_PIN (int) ; 
 scalar_t__ QUIRK_IN2_DIFF (int) ; 
 scalar_t__ QUIRK_INV_JD1_1 (int) ; 
 int QUIRK_JD_MODE (int) ; 
 scalar_t__ QUIRK_LEVEL_IRQ (int) ; 
 int /*<<< orphan*/  RT5645_ADDA_CLK1 ; 
 int /*<<< orphan*/  RT5645_AD_DA_MIXER ; 
 int /*<<< orphan*/  RT5645_A_JD_CTRL1 ; 
 int /*<<< orphan*/  RT5645_CLSD_OUT_CTRL ; 
#define  RT5645_DEVICE_ID 136 
 int RT5645_DMIC_1_DP_GPIO11 ; 
 int RT5645_DMIC_1_DP_GPIO5 ; 
 int RT5645_DMIC_1_DP_IN2N ; 
 int RT5645_DMIC_1_DP_MASK ; 
 int RT5645_DMIC_2_DP_GPIO10 ; 
 int RT5645_DMIC_2_DP_GPIO12 ; 
 int RT5645_DMIC_2_DP_GPIO6 ; 
 int RT5645_DMIC_2_DP_IN2P ; 
 int RT5645_DMIC_2_DP_MASK ; 
 int /*<<< orphan*/  RT5645_DMIC_CTRL1 ; 
#define  RT5645_DMIC_DATA_GPIO10 135 
#define  RT5645_DMIC_DATA_GPIO11 134 
#define  RT5645_DMIC_DATA_GPIO12 133 
#define  RT5645_DMIC_DATA_GPIO5 132 
#define  RT5645_DMIC_DATA_GPIO6 131 
#define  RT5645_DMIC_DATA_IN2N 130 
#define  RT5645_DMIC_DATA_IN2P 129 
 int /*<<< orphan*/  RT5645_GEN_CTRL3 ; 
 int RT5645_GP10_PIN_DMIC2_SDA ; 
 int RT5645_GP10_PIN_MASK ; 
 int RT5645_GP11_PIN_DMIC1_SDA ; 
 int RT5645_GP11_PIN_MASK ; 
 int RT5645_GP12_PIN_DMIC2_SDA ; 
 int RT5645_GP12_PIN_MASK ; 
 int RT5645_GP1_PIN_IRQ ; 
 int RT5645_GP2_PIN_DMIC1_SCL ; 
 int RT5645_GP2_PIN_MASK ; 
 int RT5645_GP5_PIN_DMIC1_SDA ; 
 int RT5645_GP5_PIN_MASK ; 
 int RT5645_GP6_PIN_DMIC2_SDA ; 
 int RT5645_GP6_PIN_MASK ; 
 int /*<<< orphan*/  RT5645_GPIO_CTRL1 ; 
 int /*<<< orphan*/  RT5645_HPO_MIXER ; 
 int RT5645_I2S2_DAC_PIN_GPIO ; 
 int RT5645_I2S2_DAC_PIN_MASK ; 
 int RT5645_I2S_PD1_2 ; 
 int RT5645_I2S_PD1_MASK ; 
 int /*<<< orphan*/  RT5645_IN2_CTRL ; 
 int RT5645_IN_DF2 ; 
 int RT5645_IRQ_CLK_GATE_CTRL ; 
 int RT5645_IRQ_CLK_INT ; 
 int /*<<< orphan*/  RT5645_IRQ_CTRL2 ; 
 int RT5645_IRQ_JD_1_1_EN ; 
 int RT5645_IRQ_PSV_MODE ; 
 int RT5645_JD1_MODE_0 ; 
 int RT5645_JD1_MODE_1 ; 
 int RT5645_JD1_MODE_2 ; 
 int RT5645_JD1_MODE_MASK ; 
 int RT5645_JD_1_1_INV ; 
 int RT5645_JD_1_1_MASK ; 
 int RT5645_JD_PSV_MODE ; 
 int RT5645_MIC2_OVCD_EN ; 
 int /*<<< orphan*/  RT5645_MICBIAS ; 
 int /*<<< orphan*/  RT5645_RESET ; 
 int /*<<< orphan*/  RT5645_VENDOR_ID ; 
 int /*<<< orphan*/  RT5645_VENDOR_ID2 ; 
#define  RT5650_DEVICE_ID 128 
 int /*<<< orphan*/  TIME_TO_POWER_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rt5645_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct rt5645_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmi_platform_data ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct rt5645_priv*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5645_priv*) ; 
 TYPE_1__* init_list ; 
 struct rt5645_platform_data jd_mode3_platform_data ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int quirk ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (struct regmap*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct rt5645_priv*) ; 
 int /*<<< orphan*/  rt5645_btn_check_callback ; 
 scalar_t__ rt5645_check_dp (int /*<<< orphan*/ *) ; 
 TYPE_1__* rt5645_dai ; 
 int /*<<< orphan*/  rt5645_irq ; 
 int /*<<< orphan*/  rt5645_jack_detect_work ; 
 int /*<<< orphan*/  rt5645_parse_dt (struct rt5645_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5645_rcclock_work ; 
 int /*<<< orphan*/  rt5645_regmap ; 
 int /*<<< orphan*/ * rt5645_supply_names ; 
 TYPE_1__* rt5650_init_list ; 
 int /*<<< orphan*/  rt5650_regmap ; 
 int /*<<< orphan*/  soc_component_dev_rt5645 ; 
 int /*<<< orphan*/  temp_regmap ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5645_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt5645_platform_data *pdata = dev_get_platdata(&i2c->dev);
	const struct dmi_system_id *dmi_data;
	struct rt5645_priv *rt5645;
	int ret, i;
	unsigned int val;
	struct regmap *regmap;

	rt5645 = devm_kzalloc(&i2c->dev, sizeof(struct rt5645_priv),
				GFP_KERNEL);
	if (rt5645 == NULL)
		return -ENOMEM;

	rt5645->i2c = i2c;
	i2c_set_clientdata(i2c, rt5645);

	dmi_data = dmi_first_match(dmi_platform_data);
	if (dmi_data) {
		dev_info(&i2c->dev, "Detected %s platform\n", dmi_data->ident);
		pdata = dmi_data->driver_data;
	}

	if (pdata)
		rt5645->pdata = *pdata;
	else if (rt5645_check_dp(&i2c->dev))
		rt5645_parse_dt(rt5645, &i2c->dev);
	else
		rt5645->pdata = jd_mode3_platform_data;

	if (quirk != -1) {
		rt5645->pdata.in2_diff = QUIRK_IN2_DIFF(quirk);
		rt5645->pdata.level_trigger_irq = QUIRK_LEVEL_IRQ(quirk);
		rt5645->pdata.inv_jd1_1 = QUIRK_INV_JD1_1(quirk);
		rt5645->pdata.jd_mode = QUIRK_JD_MODE(quirk);
		rt5645->pdata.dmic1_data_pin = QUIRK_DMIC1_DATA_PIN(quirk);
		rt5645->pdata.dmic2_data_pin = QUIRK_DMIC2_DATA_PIN(quirk);
	}

	rt5645->gpiod_hp_det = devm_gpiod_get_optional(&i2c->dev, "hp-detect",
						       GPIOD_IN);

	if (IS_ERR(rt5645->gpiod_hp_det)) {
		dev_info(&i2c->dev, "failed to initialize gpiod\n");
		ret = PTR_ERR(rt5645->gpiod_hp_det);
		/*
		 * Continue if optional gpiod is missing, bail for all other
		 * errors, including -EPROBE_DEFER
		 */
		if (ret != -ENOENT)
			return ret;
	}

	for (i = 0; i < ARRAY_SIZE(rt5645->supplies); i++)
		rt5645->supplies[i].supply = rt5645_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev,
				      ARRAY_SIZE(rt5645->supplies),
				      rt5645->supplies);
	if (ret) {
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(rt5645->supplies),
				    rt5645->supplies);
	if (ret) {
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	regmap = devm_regmap_init_i2c(i2c, &temp_regmap);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to allocate temp register map: %d\n",
			ret);
		return ret;
	}

	/*
	 * Read after 400msec, as it is the interval required between
	 * read and power On.
	 */
	msleep(TIME_TO_POWER_MS);
	regmap_read(regmap, RT5645_VENDOR_ID2, &val);

	switch (val) {
	case RT5645_DEVICE_ID:
		rt5645->regmap = devm_regmap_init_i2c(i2c, &rt5645_regmap);
		rt5645->codec_type = CODEC_TYPE_RT5645;
		break;
	case RT5650_DEVICE_ID:
		rt5645->regmap = devm_regmap_init_i2c(i2c, &rt5650_regmap);
		rt5645->codec_type = CODEC_TYPE_RT5650;
		break;
	default:
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5645 or rt5650\n",
			val);
		ret = -ENODEV;
		goto err_enable;
	}

	if (IS_ERR(rt5645->regmap)) {
		ret = PTR_ERR(rt5645->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	regmap_write(rt5645->regmap, RT5645_RESET, 0);

	regmap_read(regmap, RT5645_VENDOR_ID, &val);
	rt5645->v_id = val & 0xff;

	regmap_write(rt5645->regmap, RT5645_AD_DA_MIXER, 0x8080);

	ret = regmap_register_patch(rt5645->regmap, init_list,
				    ARRAY_SIZE(init_list));
	if (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	if (rt5645->codec_type == CODEC_TYPE_RT5650) {
		ret = regmap_register_patch(rt5645->regmap, rt5650_init_list,
				    ARRAY_SIZE(rt5650_init_list));
		if (ret != 0)
			dev_warn(&i2c->dev, "Apply rt5650 patch failed: %d\n",
					   ret);
	}

	regmap_update_bits(rt5645->regmap, RT5645_CLSD_OUT_CTRL, 0xc0, 0xc0);

	if (rt5645->pdata.in2_diff)
		regmap_update_bits(rt5645->regmap, RT5645_IN2_CTRL,
					RT5645_IN_DF2, RT5645_IN_DF2);

	if (rt5645->pdata.dmic1_data_pin || rt5645->pdata.dmic2_data_pin) {
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP2_PIN_MASK, RT5645_GP2_PIN_DMIC1_SCL);
	}
	switch (rt5645->pdata.dmic1_data_pin) {
	case RT5645_DMIC_DATA_IN2N:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_1_DP_MASK, RT5645_DMIC_1_DP_IN2N);
		break;

	case RT5645_DMIC_DATA_GPIO5:
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_I2S2_DAC_PIN_MASK, RT5645_I2S2_DAC_PIN_GPIO);
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_1_DP_MASK, RT5645_DMIC_1_DP_GPIO5);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP5_PIN_MASK, RT5645_GP5_PIN_DMIC1_SDA);
		break;

	case RT5645_DMIC_DATA_GPIO11:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_1_DP_MASK, RT5645_DMIC_1_DP_GPIO11);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP11_PIN_MASK,
			RT5645_GP11_PIN_DMIC1_SDA);
		break;

	default:
		break;
	}

	switch (rt5645->pdata.dmic2_data_pin) {
	case RT5645_DMIC_DATA_IN2P:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_IN2P);
		break;

	case RT5645_DMIC_DATA_GPIO6:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_GPIO6);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP6_PIN_MASK, RT5645_GP6_PIN_DMIC2_SDA);
		break;

	case RT5645_DMIC_DATA_GPIO10:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_GPIO10);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP10_PIN_MASK,
			RT5645_GP10_PIN_DMIC2_SDA);
		break;

	case RT5645_DMIC_DATA_GPIO12:
		regmap_update_bits(rt5645->regmap, RT5645_DMIC_CTRL1,
			RT5645_DMIC_2_DP_MASK, RT5645_DMIC_2_DP_GPIO12);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
			RT5645_GP12_PIN_MASK,
			RT5645_GP12_PIN_DMIC2_SDA);
		break;

	default:
		break;
	}

	if (rt5645->pdata.jd_mode) {
		regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL3,
				   RT5645_IRQ_CLK_GATE_CTRL,
				   RT5645_IRQ_CLK_GATE_CTRL);
		regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
				   RT5645_IRQ_CLK_INT, RT5645_IRQ_CLK_INT);
		regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				   RT5645_IRQ_JD_1_1_EN, RT5645_IRQ_JD_1_1_EN);
		regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL3,
				   RT5645_JD_PSV_MODE, RT5645_JD_PSV_MODE);
		regmap_update_bits(rt5645->regmap, RT5645_HPO_MIXER,
				   RT5645_IRQ_PSV_MODE, RT5645_IRQ_PSV_MODE);
		regmap_update_bits(rt5645->regmap, RT5645_MICBIAS,
				   RT5645_MIC2_OVCD_EN, RT5645_MIC2_OVCD_EN);
		regmap_update_bits(rt5645->regmap, RT5645_GPIO_CTRL1,
				   RT5645_GP1_PIN_IRQ, RT5645_GP1_PIN_IRQ);
		switch (rt5645->pdata.jd_mode) {
		case 1:
			regmap_update_bits(rt5645->regmap, RT5645_A_JD_CTRL1,
					   RT5645_JD1_MODE_MASK,
					   RT5645_JD1_MODE_0);
			break;
		case 2:
			regmap_update_bits(rt5645->regmap, RT5645_A_JD_CTRL1,
					   RT5645_JD1_MODE_MASK,
					   RT5645_JD1_MODE_1);
			break;
		case 3:
			regmap_update_bits(rt5645->regmap, RT5645_A_JD_CTRL1,
					   RT5645_JD1_MODE_MASK,
					   RT5645_JD1_MODE_2);
			break;
		default:
			break;
		}
		if (rt5645->pdata.inv_jd1_1) {
			regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				RT5645_JD_1_1_MASK, RT5645_JD_1_1_INV);
		}
	}

	regmap_update_bits(rt5645->regmap, RT5645_ADDA_CLK1,
		RT5645_I2S_PD1_MASK, RT5645_I2S_PD1_2);

	if (rt5645->pdata.level_trigger_irq) {
		regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
			RT5645_JD_1_1_MASK, RT5645_JD_1_1_INV);
	}
	timer_setup(&rt5645->btn_check_timer, rt5645_btn_check_callback, 0);

	INIT_DELAYED_WORK(&rt5645->jack_detect_work, rt5645_jack_detect_work);
	INIT_DELAYED_WORK(&rt5645->rcclock_work, rt5645_rcclock_work);

	if (rt5645->i2c->irq) {
		ret = request_threaded_irq(rt5645->i2c->irq, NULL, rt5645_irq,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5645", rt5645);
		if (ret) {
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);
			goto err_enable;
		}
	}

	ret = devm_snd_soc_register_component(&i2c->dev, &soc_component_dev_rt5645,
				     rt5645_dai, ARRAY_SIZE(rt5645_dai));
	if (ret)
		goto err_irq;

	return 0;

err_irq:
	if (rt5645->i2c->irq)
		free_irq(rt5645->i2c->irq, rt5645);
err_enable:
	regulator_bulk_disable(ARRAY_SIZE(rt5645->supplies), rt5645->supplies);
	return ret;
}