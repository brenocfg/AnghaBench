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
struct rt5659_platform_data {int dmic1_data_pin; int dmic2_data_pin; int jd_src; scalar_t__ in4_diff; scalar_t__ in3_diff; scalar_t__ in1_diff; } ;
struct rt5659_priv {int /*<<< orphan*/ * regmap; int /*<<< orphan*/  jack_detect_work; struct rt5659_platform_data pdata; int /*<<< orphan*/ * mclk; void* gpiod_reset; int /*<<< orphan*/ * gpiod_ldo1_en; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int DEVICE_ID ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT5659_DEVICE_ID ; 
#define  RT5659_DMIC1_DATA_GPIO11 137 
#define  RT5659_DMIC1_DATA_GPIO5 136 
#define  RT5659_DMIC1_DATA_GPIO9 135 
#define  RT5659_DMIC1_DATA_IN2N 134 
 int RT5659_DMIC1_NULL ; 
#define  RT5659_DMIC2_DATA_GPIO10 133 
#define  RT5659_DMIC2_DATA_GPIO12 132 
#define  RT5659_DMIC2_DATA_GPIO6 131 
#define  RT5659_DMIC2_DATA_IN2P 130 
 int RT5659_DMIC2_NULL ; 
 int RT5659_DMIC_1_DP_GPIO11 ; 
 int RT5659_DMIC_1_DP_GPIO5 ; 
 int RT5659_DMIC_1_DP_GPIO9 ; 
 int RT5659_DMIC_1_DP_IN2N ; 
 int RT5659_DMIC_1_DP_MASK ; 
 int RT5659_DMIC_2_DP_GPIO10 ; 
 int RT5659_DMIC_2_DP_GPIO12 ; 
 int RT5659_DMIC_2_DP_GPIO6 ; 
 int RT5659_DMIC_2_DP_IN2P ; 
 int RT5659_DMIC_2_DP_MASK ; 
 int /*<<< orphan*/  RT5659_DMIC_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_EJD_CTRL_1 ; 
 int RT5659_GP10_PIN_DMIC2_SDA ; 
 int RT5659_GP10_PIN_GPIO10 ; 
 int RT5659_GP10_PIN_MASK ; 
 int RT5659_GP11_PIN_DMIC1_SDA ; 
 int RT5659_GP11_PIN_GPIO11 ; 
 int RT5659_GP11_PIN_MASK ; 
 int RT5659_GP12_PIN_DMIC2_SDA ; 
 int RT5659_GP12_PIN_GPIO12 ; 
 int RT5659_GP12_PIN_MASK ; 
 int RT5659_GP1_PIN_IRQ ; 
 int RT5659_GP1_PIN_MASK ; 
 int RT5659_GP2_PIN_DMIC1_SCL ; 
 int RT5659_GP2_PIN_GPIO2 ; 
 int RT5659_GP2_PIN_MASK ; 
 int RT5659_GP5_PIN_DMIC1_SDA ; 
 int RT5659_GP5_PIN_GPIO5 ; 
 int RT5659_GP5_PIN_MASK ; 
 int RT5659_GP6_PIN_DMIC2_SDA ; 
 int RT5659_GP6_PIN_GPIO6 ; 
 int RT5659_GP6_PIN_MASK ; 
 int RT5659_GP9_PIN_DMIC1_SDA ; 
 int RT5659_GP9_PIN_GPIO9 ; 
 int RT5659_GP9_PIN_MASK ; 
 int /*<<< orphan*/  RT5659_GPIO_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_GPIO_CTRL_3 ; 
 int RT5659_I2S2_PIN_GPIO ; 
 int RT5659_I2S2_PIN_MASK ; 
 int RT5659_IN1_DF_MASK ; 
 int /*<<< orphan*/  RT5659_IN1_IN2 ; 
 int RT5659_IN3_DF_MASK ; 
 int /*<<< orphan*/  RT5659_IN3_IN4 ; 
 int RT5659_IN4_DF_MASK ; 
 int /*<<< orphan*/  RT5659_IRQ_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_IRQ_CTRL_2 ; 
#define  RT5659_JD3 129 
 int /*<<< orphan*/  RT5659_JD_CTRL_1 ; 
#define  RT5659_JD_HDA_HEADER 128 
 int /*<<< orphan*/  RT5659_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5659_PWR_ANLG_2 ; 
 int RT5659_PWR_MB ; 
 int /*<<< orphan*/  RT5659_RC_CLK_CTRL ; 
 int /*<<< orphan*/  RT5659_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rt5659_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct rt5659_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct rt5659_priv*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5659_priv*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt5659_calibrate (struct rt5659_priv*) ; 
 int /*<<< orphan*/  rt5659_dai ; 
 int /*<<< orphan*/  rt5659_intel_hd_header_probe_setup (struct rt5659_priv*) ; 
 int /*<<< orphan*/  rt5659_irq ; 
 int /*<<< orphan*/  rt5659_jack_detect_intel_hd_header ; 
 int /*<<< orphan*/  rt5659_jack_detect_work ; 
 int /*<<< orphan*/  rt5659_parse_dt (struct rt5659_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5659_regmap ; 
 int /*<<< orphan*/  soc_component_dev_rt5659 ; 

__attribute__((used)) static int rt5659_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt5659_platform_data *pdata = dev_get_platdata(&i2c->dev);
	struct rt5659_priv *rt5659;
	int ret;
	unsigned int val;

	rt5659 = devm_kzalloc(&i2c->dev, sizeof(struct rt5659_priv),
		GFP_KERNEL);

	if (rt5659 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt5659);

	if (pdata)
		rt5659->pdata = *pdata;
	else
		rt5659_parse_dt(rt5659, &i2c->dev);

	rt5659->gpiod_ldo1_en = devm_gpiod_get_optional(&i2c->dev, "ldo1-en",
							GPIOD_OUT_HIGH);
	if (IS_ERR(rt5659->gpiod_ldo1_en))
		dev_warn(&i2c->dev, "Request ldo1-en GPIO failed\n");

	rt5659->gpiod_reset = devm_gpiod_get_optional(&i2c->dev, "reset",
							GPIOD_OUT_HIGH);

	/* Sleep for 300 ms miniumum */
	msleep(300);

	rt5659->regmap = devm_regmap_init_i2c(i2c, &rt5659_regmap);
	if (IS_ERR(rt5659->regmap)) {
		ret = PTR_ERR(rt5659->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	regmap_read(rt5659->regmap, RT5659_DEVICE_ID, &val);
	if (val != DEVICE_ID) {
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt5659\n", val);
		return -ENODEV;
	}

	regmap_write(rt5659->regmap, RT5659_RESET, 0);

	/* Check if MCLK provided */
	rt5659->mclk = devm_clk_get(&i2c->dev, "mclk");
	if (IS_ERR(rt5659->mclk)) {
		if (PTR_ERR(rt5659->mclk) != -ENOENT)
			return PTR_ERR(rt5659->mclk);
		/* Otherwise mark the mclk pointer to NULL */
		rt5659->mclk = NULL;
	}

	rt5659_calibrate(rt5659);

	/* line in diff mode*/
	if (rt5659->pdata.in1_diff)
		regmap_update_bits(rt5659->regmap, RT5659_IN1_IN2,
			RT5659_IN1_DF_MASK, RT5659_IN1_DF_MASK);
	if (rt5659->pdata.in3_diff)
		regmap_update_bits(rt5659->regmap, RT5659_IN3_IN4,
			RT5659_IN3_DF_MASK, RT5659_IN3_DF_MASK);
	if (rt5659->pdata.in4_diff)
		regmap_update_bits(rt5659->regmap, RT5659_IN3_IN4,
			RT5659_IN4_DF_MASK, RT5659_IN4_DF_MASK);

	/* DMIC pin*/
	if (rt5659->pdata.dmic1_data_pin != RT5659_DMIC1_NULL ||
		rt5659->pdata.dmic2_data_pin != RT5659_DMIC2_NULL) {
		regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
			RT5659_GP2_PIN_MASK, RT5659_GP2_PIN_DMIC1_SCL);

		switch (rt5659->pdata.dmic1_data_pin) {
		case RT5659_DMIC1_DATA_IN2N:
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_IN2N);
			break;

		case RT5659_DMIC1_DATA_GPIO5:
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_3,
				RT5659_I2S2_PIN_MASK,
				RT5659_I2S2_PIN_GPIO);
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_GPIO5);
			regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				RT5659_GP5_PIN_MASK, RT5659_GP5_PIN_DMIC1_SDA);
			break;

		case RT5659_DMIC1_DATA_GPIO9:
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_GPIO9);
			regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				RT5659_GP9_PIN_MASK, RT5659_GP9_PIN_DMIC1_SDA);
			break;

		case RT5659_DMIC1_DATA_GPIO11:
			regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
				RT5659_DMIC_1_DP_MASK, RT5659_DMIC_1_DP_GPIO11);
			regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				RT5659_GP11_PIN_MASK,
				RT5659_GP11_PIN_DMIC1_SDA);
			break;

		default:
			dev_dbg(&i2c->dev, "no DMIC1\n");
			break;
		}

		switch (rt5659->pdata.dmic2_data_pin) {
		case RT5659_DMIC2_DATA_IN2P:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_IN2P);
			break;

		case RT5659_DMIC2_DATA_GPIO6:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_GPIO6);
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_1,
				RT5659_GP6_PIN_MASK,
				RT5659_GP6_PIN_DMIC2_SDA);
			break;

		case RT5659_DMIC2_DATA_GPIO10:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_GPIO10);
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_1,
				RT5659_GP10_PIN_MASK,
				RT5659_GP10_PIN_DMIC2_SDA);
			break;

		case RT5659_DMIC2_DATA_GPIO12:
			regmap_update_bits(rt5659->regmap,
				RT5659_DMIC_CTRL_1,
				RT5659_DMIC_2_DP_MASK,
				RT5659_DMIC_2_DP_GPIO12);
			regmap_update_bits(rt5659->regmap,
				RT5659_GPIO_CTRL_1,
				RT5659_GP12_PIN_MASK,
				RT5659_GP12_PIN_DMIC2_SDA);
			break;

		default:
			dev_dbg(&i2c->dev, "no DMIC2\n");
			break;

		}
	} else {
		regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
			RT5659_GP2_PIN_MASK | RT5659_GP5_PIN_MASK |
			RT5659_GP9_PIN_MASK | RT5659_GP11_PIN_MASK |
			RT5659_GP6_PIN_MASK | RT5659_GP10_PIN_MASK |
			RT5659_GP12_PIN_MASK,
			RT5659_GP2_PIN_GPIO2 | RT5659_GP5_PIN_GPIO5 |
			RT5659_GP9_PIN_GPIO9 | RT5659_GP11_PIN_GPIO11 |
			RT5659_GP6_PIN_GPIO6 | RT5659_GP10_PIN_GPIO10 |
			RT5659_GP12_PIN_GPIO12);
		regmap_update_bits(rt5659->regmap, RT5659_DMIC_CTRL_1,
			RT5659_DMIC_1_DP_MASK | RT5659_DMIC_2_DP_MASK,
			RT5659_DMIC_1_DP_IN2N | RT5659_DMIC_2_DP_IN2P);
	}

	switch (rt5659->pdata.jd_src) {
	case RT5659_JD3:
		regmap_write(rt5659->regmap, RT5659_EJD_CTRL_1, 0xa880);
		regmap_write(rt5659->regmap, RT5659_RC_CLK_CTRL, 0x9000);
		regmap_write(rt5659->regmap, RT5659_GPIO_CTRL_1, 0xc800);
		regmap_update_bits(rt5659->regmap, RT5659_PWR_ANLG_1,
				RT5659_PWR_MB, RT5659_PWR_MB);
		regmap_write(rt5659->regmap, RT5659_PWR_ANLG_2, 0x0001);
		regmap_write(rt5659->regmap, RT5659_IRQ_CTRL_2, 0x0040);
		INIT_DELAYED_WORK(&rt5659->jack_detect_work,
			rt5659_jack_detect_work);
		break;
	case RT5659_JD_HDA_HEADER:
		regmap_write(rt5659->regmap, RT5659_GPIO_CTRL_3, 0x8000);
		regmap_write(rt5659->regmap, RT5659_RC_CLK_CTRL, 0x0900);
		regmap_write(rt5659->regmap, RT5659_EJD_CTRL_1,  0x70c0);
		regmap_write(rt5659->regmap, RT5659_JD_CTRL_1,   0x2000);
		regmap_write(rt5659->regmap, RT5659_IRQ_CTRL_1,  0x0040);
		INIT_DELAYED_WORK(&rt5659->jack_detect_work,
			rt5659_jack_detect_intel_hd_header);
		rt5659_intel_hd_header_probe_setup(rt5659);
		break;
	default:
		break;
	}

	if (i2c->irq) {
		ret = devm_request_threaded_irq(&i2c->dev, i2c->irq, NULL,
			rt5659_irq, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			| IRQF_ONESHOT, "rt5659", rt5659);
		if (ret)
			dev_err(&i2c->dev, "Failed to reguest IRQ: %d\n", ret);

		/* Enable IRQ output for GPIO1 pin any way */
		regmap_update_bits(rt5659->regmap, RT5659_GPIO_CTRL_1,
				   RT5659_GP1_PIN_MASK, RT5659_GP1_PIN_IRQ);
	}

	return devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_rt5659,
			rt5659_dai, ARRAY_SIZE(rt5659_dai));
}