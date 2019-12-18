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
struct rt5651_priv {int hp_mute; int /*<<< orphan*/  irq; int /*<<< orphan*/  jack_detect_work; int /*<<< orphan*/  bp_work; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5651_DEVICE_ID ; 
 int RT5651_DEVICE_ID_VALUE ; 
 int /*<<< orphan*/  RT5651_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rt5651_priv*) ; 
 struct rt5651_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct rt5651_priv*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5651_priv*) ; 
 int /*<<< orphan*/  init_list ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5651_button_press_work ; 
 int /*<<< orphan*/  rt5651_cancel_work ; 
 int /*<<< orphan*/  rt5651_dai ; 
 int /*<<< orphan*/  rt5651_irq ; 
 int /*<<< orphan*/  rt5651_jack_detect_work ; 
 int /*<<< orphan*/  rt5651_regmap ; 
 int /*<<< orphan*/  soc_component_dev_rt5651 ; 

__attribute__((used)) static int rt5651_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt5651_priv *rt5651;
	int ret;
	int err;

	rt5651 = devm_kzalloc(&i2c->dev, sizeof(*rt5651),
				GFP_KERNEL);
	if (NULL == rt5651)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt5651);

	rt5651->regmap = devm_regmap_init_i2c(i2c, &rt5651_regmap);
	if (IS_ERR(rt5651->regmap)) {
		ret = PTR_ERR(rt5651->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	err = regmap_read(rt5651->regmap, RT5651_DEVICE_ID, &ret);
	if (err)
		return err;

	if (ret != RT5651_DEVICE_ID_VALUE) {
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5651\n", ret);
		return -ENODEV;
	}

	regmap_write(rt5651->regmap, RT5651_RESET, 0);

	ret = regmap_register_patch(rt5651->regmap, init_list,
				    ARRAY_SIZE(init_list));
	if (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	rt5651->irq = i2c->irq;
	rt5651->hp_mute = true;

	INIT_DELAYED_WORK(&rt5651->bp_work, rt5651_button_press_work);
	INIT_WORK(&rt5651->jack_detect_work, rt5651_jack_detect_work);

	/* Make sure work is stopped on probe-error / remove */
	ret = devm_add_action_or_reset(&i2c->dev, rt5651_cancel_work, rt5651);
	if (ret)
		return ret;

	ret = devm_request_irq(&i2c->dev, rt5651->irq, rt5651_irq,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING
			       | IRQF_ONESHOT, "rt5651", rt5651);
	if (ret == 0) {
		/* Gets re-enabled by rt5651_set_jack() */
		disable_irq(rt5651->irq);
	} else {
		dev_warn(&i2c->dev, "Failed to reguest IRQ %d: %d\n",
			 rt5651->irq, ret);
		rt5651->irq = -ENXIO;
	}

	ret = devm_snd_soc_register_component(&i2c->dev,
				&soc_component_dev_rt5651,
				rt5651_dai, ARRAY_SIZE(rt5651_dai));

	return ret;
}