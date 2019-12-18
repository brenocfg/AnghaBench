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
struct device {int dummy; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  irq; } ;
struct es8316_priv {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct es8316_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct es8316_priv*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es8316_dai ; 
 int /*<<< orphan*/  es8316_irq ; 
 int /*<<< orphan*/  es8316_regmap ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct es8316_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_component_dev_es8316 ; 

__attribute__((used)) static int es8316_i2c_probe(struct i2c_client *i2c_client,
			    const struct i2c_device_id *id)
{
	struct device *dev = &i2c_client->dev;
	struct es8316_priv *es8316;
	int ret;

	es8316 = devm_kzalloc(&i2c_client->dev, sizeof(struct es8316_priv),
			      GFP_KERNEL);
	if (es8316 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c_client, es8316);

	es8316->regmap = devm_regmap_init_i2c(i2c_client, &es8316_regmap);
	if (IS_ERR(es8316->regmap))
		return PTR_ERR(es8316->regmap);

	es8316->irq = i2c_client->irq;
	mutex_init(&es8316->lock);

	ret = devm_request_threaded_irq(dev, es8316->irq, NULL, es8316_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"es8316", es8316);
	if (ret == 0) {
		/* Gets re-enabled by es8316_set_jack() */
		disable_irq(es8316->irq);
	} else {
		dev_warn(dev, "Failed to get IRQ %d: %d\n", es8316->irq, ret);
		es8316->irq = -ENXIO;
	}

	return devm_snd_soc_register_component(&i2c_client->dev,
				      &soc_component_dev_es8316,
				      &es8316_dai, 1);
}