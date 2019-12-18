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
struct rt5640_priv {int hp_mute; int /*<<< orphan*/  irq; int /*<<< orphan*/  jack_work; int /*<<< orphan*/  bp_work; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ldo1_en; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int RT5640_DEVICE_ID ; 
 int /*<<< orphan*/  RT5640_DUMMY1 ; 
 int /*<<< orphan*/  RT5640_MCLK_DET ; 
 int /*<<< orphan*/  RT5640_RESET ; 
 int /*<<< orphan*/  RT5640_VENDOR_ID2 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int,...) ; 
 int devm_add_action_or_reset (TYPE_1__*,int /*<<< orphan*/ ,struct rt5640_priv*) ; 
 int devm_gpio_request_one (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rt5640_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct rt5640_priv*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5640_priv*) ; 
 int /*<<< orphan*/  init_list ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5640_button_press_work ; 
 int /*<<< orphan*/  rt5640_cancel_work ; 
 int /*<<< orphan*/  rt5640_dai ; 
 int /*<<< orphan*/  rt5640_irq ; 
 int /*<<< orphan*/  rt5640_jack_work ; 
 int rt5640_parse_dt (struct rt5640_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5640_regmap ; 
 int /*<<< orphan*/  soc_component_dev_rt5640 ; 

__attribute__((used)) static int rt5640_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt5640_priv *rt5640;
	int ret;
	unsigned int val;

	rt5640 = devm_kzalloc(&i2c->dev,
				sizeof(struct rt5640_priv),
				GFP_KERNEL);
	if (NULL == rt5640)
		return -ENOMEM;
	i2c_set_clientdata(i2c, rt5640);

	if (i2c->dev.of_node) {
		ret = rt5640_parse_dt(rt5640, i2c->dev.of_node);
		if (ret)
			return ret;
	} else
		rt5640->ldo1_en = -EINVAL;

	rt5640->regmap = devm_regmap_init_i2c(i2c, &rt5640_regmap);
	if (IS_ERR(rt5640->regmap)) {
		ret = PTR_ERR(rt5640->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	if (gpio_is_valid(rt5640->ldo1_en)) {
		ret = devm_gpio_request_one(&i2c->dev, rt5640->ldo1_en,
					    GPIOF_OUT_INIT_HIGH,
					    "RT5640 LDO1_EN");
		if (ret < 0) {
			dev_err(&i2c->dev, "Failed to request LDO1_EN %d: %d\n",
				rt5640->ldo1_en, ret);
			return ret;
		}
		msleep(400);
	}

	regmap_read(rt5640->regmap, RT5640_VENDOR_ID2, &val);
	if (val != RT5640_DEVICE_ID) {
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5640/39\n", val);
		return -ENODEV;
	}

	regmap_write(rt5640->regmap, RT5640_RESET, 0);

	ret = regmap_register_patch(rt5640->regmap, init_list,
				    ARRAY_SIZE(init_list));
	if (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_update_bits(rt5640->regmap, RT5640_DUMMY1,
				RT5640_MCLK_DET, RT5640_MCLK_DET);

	rt5640->hp_mute = true;
	rt5640->irq = i2c->irq;
	INIT_DELAYED_WORK(&rt5640->bp_work, rt5640_button_press_work);
	INIT_WORK(&rt5640->jack_work, rt5640_jack_work);

	/* Make sure work is stopped on probe-error / remove */
	ret = devm_add_action_or_reset(&i2c->dev, rt5640_cancel_work, rt5640);
	if (ret)
		return ret;

	ret = devm_request_irq(&i2c->dev, rt5640->irq, rt5640_irq,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			       | IRQF_ONESHOT, "rt5640", rt5640);
	if (ret == 0) {
		/* Gets re-enabled by rt5640_set_jack() */
		disable_irq(rt5640->irq);
	} else {
		dev_warn(&i2c->dev, "Failed to reguest IRQ %d: %d\n",
			 rt5640->irq, ret);
		rt5640->irq = -ENXIO;
	}

	return devm_snd_soc_register_component(&i2c->dev,
				      &soc_component_dev_rt5640,
				      rt5640_dai, ARRAY_SIZE(rt5640_dai));
}