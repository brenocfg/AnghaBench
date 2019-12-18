#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct wm8904_priv {int devtype; TYPE_2__* supplies; int /*<<< orphan*/  regmap; TYPE_1__* pdata; int /*<<< orphan*/  mclk; } ;
struct of_device_id {scalar_t__ data; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_14__ {TYPE_1__* platform_data; scalar_t__ of_node; } ;
struct i2c_client {TYPE_4__ dev; } ;
typedef  enum wm8904_type { ____Placeholder_wm8904_type } wm8904_type ;
struct TYPE_13__ {int /*<<< orphan*/  supply; } ;
struct TYPE_12__ {int* gpio_cfg; int* mic_cfg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ WM8904_ADC_DIGITAL_VOLUME_LEFT ; 
 scalar_t__ WM8904_ADC_DIGITAL_VOLUME_RIGHT ; 
 int WM8904_ADC_VU ; 
 scalar_t__ WM8904_ANALOGUE_OUT1_LEFT ; 
 scalar_t__ WM8904_ANALOGUE_OUT1_RIGHT ; 
 scalar_t__ WM8904_ANALOGUE_OUT2_LEFT ; 
 scalar_t__ WM8904_ANALOGUE_OUT2_RIGHT ; 
 scalar_t__ WM8904_BIAS_CONTROL_0 ; 
 scalar_t__ WM8904_CLASS_W_0 ; 
 scalar_t__ WM8904_CLOCK_RATES_0 ; 
 int WM8904_CP_DYN_PWR ; 
 scalar_t__ WM8904_DAC_DIGITAL_VOLUME_LEFT ; 
 scalar_t__ WM8904_DAC_DIGITAL_VOLUME_RIGHT ; 
 int WM8904_DAC_VU ; 
 scalar_t__ WM8904_GPIO_CONTROL_1 ; 
 int WM8904_GPIO_REGS ; 
 int WM8904_HPOUTLZC ; 
 int WM8904_HPOUTRZC ; 
 int WM8904_HPOUT_VU ; 
 int WM8904_LINEOUTLZC ; 
 int WM8904_LINEOUTRZC ; 
 int WM8904_LINEOUT_VU ; 
 scalar_t__ WM8904_MIC_BIAS_CONTROL_0 ; 
 int WM8904_MIC_REGS ; 
 int WM8904_POBCTRL ; 
 int /*<<< orphan*/  WM8904_REVISION ; 
 int WM8904_SR_MODE ; 
 int /*<<< orphan*/  WM8904_SW_RESET_AND_ID ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,unsigned int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,char*) ; 
 struct wm8904_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (TYPE_4__*,int,TYPE_2__*) ; 
 int devm_snd_soc_register_component (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8904_priv*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_2__*) ; 
 int regulator_bulk_enable (int,TYPE_2__*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8904 ; 
 int /*<<< orphan*/  wm8904_dai ; 
 int /*<<< orphan*/  wm8904_of_match ; 
 int /*<<< orphan*/  wm8904_regmap ; 
 int /*<<< orphan*/ * wm8904_supply_names ; 

__attribute__((used)) static int wm8904_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8904_priv *wm8904;
	unsigned int val;
	int ret, i;

	wm8904 = devm_kzalloc(&i2c->dev, sizeof(struct wm8904_priv),
			      GFP_KERNEL);
	if (wm8904 == NULL)
		return -ENOMEM;

	wm8904->mclk = devm_clk_get(&i2c->dev, "mclk");
	if (IS_ERR(wm8904->mclk)) {
		ret = PTR_ERR(wm8904->mclk);
		dev_err(&i2c->dev, "Failed to get MCLK\n");
		return ret;
	}

	wm8904->regmap = devm_regmap_init_i2c(i2c, &wm8904_regmap);
	if (IS_ERR(wm8904->regmap)) {
		ret = PTR_ERR(wm8904->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	if (i2c->dev.of_node) {
		const struct of_device_id *match;

		match = of_match_node(wm8904_of_match, i2c->dev.of_node);
		if (match == NULL)
			return -EINVAL;
		wm8904->devtype = (enum wm8904_type)match->data;
	} else {
		wm8904->devtype = id->driver_data;
	}

	i2c_set_clientdata(i2c, wm8904);
	wm8904->pdata = i2c->dev.platform_data;

	for (i = 0; i < ARRAY_SIZE(wm8904->supplies); i++)
		wm8904->supplies[i].supply = wm8904_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8904->supplies),
				      wm8904->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8904->supplies),
				    wm8904->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	ret = regmap_read(wm8904->regmap, WM8904_SW_RESET_AND_ID, &val);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		goto err_enable;
	}
	if (val != 0x8904) {
		dev_err(&i2c->dev, "Device is not a WM8904, ID is %x\n", val);
		ret = -EINVAL;
		goto err_enable;
	}

	ret = regmap_read(wm8904->regmap, WM8904_REVISION, &val);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to read device revision: %d\n",
			ret);
		goto err_enable;
	}
	dev_info(&i2c->dev, "revision %c\n", val + 'A');

	ret = regmap_write(wm8904->regmap, WM8904_SW_RESET_AND_ID, 0);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		goto err_enable;
	}

	/* Change some default settings - latch VU and enable ZC */
	regmap_update_bits(wm8904->regmap, WM8904_ADC_DIGITAL_VOLUME_LEFT,
			   WM8904_ADC_VU, WM8904_ADC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_ADC_DIGITAL_VOLUME_RIGHT,
			   WM8904_ADC_VU, WM8904_ADC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_DAC_DIGITAL_VOLUME_LEFT,
			   WM8904_DAC_VU, WM8904_DAC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_DAC_DIGITAL_VOLUME_RIGHT,
			   WM8904_DAC_VU, WM8904_DAC_VU);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT1_LEFT,
			   WM8904_HPOUT_VU | WM8904_HPOUTLZC,
			   WM8904_HPOUT_VU | WM8904_HPOUTLZC);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT1_RIGHT,
			   WM8904_HPOUT_VU | WM8904_HPOUTRZC,
			   WM8904_HPOUT_VU | WM8904_HPOUTRZC);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT2_LEFT,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTLZC,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTLZC);
	regmap_update_bits(wm8904->regmap, WM8904_ANALOGUE_OUT2_RIGHT,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTRZC,
			   WM8904_LINEOUT_VU | WM8904_LINEOUTRZC);
	regmap_update_bits(wm8904->regmap, WM8904_CLOCK_RATES_0,
			   WM8904_SR_MODE, 0);

	/* Apply configuration from the platform data. */
	if (wm8904->pdata) {
		for (i = 0; i < WM8904_GPIO_REGS; i++) {
			if (!wm8904->pdata->gpio_cfg[i])
				continue;

			regmap_update_bits(wm8904->regmap,
					   WM8904_GPIO_CONTROL_1 + i,
					   0xffff,
					   wm8904->pdata->gpio_cfg[i]);
		}

		/* Zero is the default value for these anyway */
		for (i = 0; i < WM8904_MIC_REGS; i++)
			regmap_update_bits(wm8904->regmap,
					   WM8904_MIC_BIAS_CONTROL_0 + i,
					   0xffff,
					   wm8904->pdata->mic_cfg[i]);
	}

	/* Set Class W by default - this will be managed by the Class
	 * G widget at runtime where bypass paths are available.
	 */
	regmap_update_bits(wm8904->regmap, WM8904_CLASS_W_0,
			    WM8904_CP_DYN_PWR, WM8904_CP_DYN_PWR);

	/* Use normal bias source */
	regmap_update_bits(wm8904->regmap, WM8904_BIAS_CONTROL_0,
			    WM8904_POBCTRL, 0);

	/* Can leave the device powered off until we need it */
	regcache_cache_only(wm8904->regmap, true);
	regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies), wm8904->supplies);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8904, &wm8904_dai, 1);
	if (ret != 0)
		return ret;

	return 0;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8904->supplies), wm8904->supplies);
	return ret;
}