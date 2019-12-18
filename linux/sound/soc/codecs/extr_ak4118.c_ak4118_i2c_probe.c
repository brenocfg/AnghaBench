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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak4118_priv {void* irq; void* reset; void* regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ak4118_dai ; 
 int /*<<< orphan*/  ak4118_irq_handler ; 
 int /*<<< orphan*/  ak4118_regmap ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ak4118_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct ak4118_priv*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ak4118_priv*) ; 
 int /*<<< orphan*/  soc_component_drv_ak4118 ; 

__attribute__((used)) static int ak4118_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct ak4118_priv *ak4118;
	int ret;

	ak4118 = devm_kzalloc(&i2c->dev, sizeof(struct ak4118_priv),
			      GFP_KERNEL);
	if (ak4118 == NULL)
		return -ENOMEM;

	ak4118->regmap = devm_regmap_init_i2c(i2c, &ak4118_regmap);
	if (IS_ERR(ak4118->regmap))
		return PTR_ERR(ak4118->regmap);

	i2c_set_clientdata(i2c, ak4118);

	ak4118->reset = devm_gpiod_get(&i2c->dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ak4118->reset)) {
		ret = PTR_ERR(ak4118->reset);
		if (ret != -EPROBE_DEFER)
			dev_err(&i2c->dev, "Failed to get reset: %d\n", ret);
		return ret;
	}

	ak4118->irq = devm_gpiod_get(&i2c->dev, "irq", GPIOD_IN);
	if (IS_ERR(ak4118->irq)) {
		ret = PTR_ERR(ak4118->irq);
		if (ret != -EPROBE_DEFER)
			dev_err(&i2c->dev, "Failed to get IRQ: %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(&i2c->dev, gpiod_to_irq(ak4118->irq),
					NULL, ak4118_irq_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"ak4118-irq", ak4118);
	if (ret < 0) {
		dev_err(&i2c->dev, "Fail to request_irq: %d\n", ret);
		return ret;
	}

	return devm_snd_soc_register_component(&i2c->dev,
				&soc_component_drv_ak4118, &ak4118_dai, 1);
}