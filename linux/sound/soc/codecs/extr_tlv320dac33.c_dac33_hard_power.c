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
struct tlv320dac33_priv {int chip_power; scalar_t__ power_gpio; int /*<<< orphan*/  mutex; int /*<<< orphan*/  supplies; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_soft_power (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dac33_hard_power(struct snd_soc_component *component, int power)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	mutex_lock(&dac33->mutex);

	/* Safety check */
	if (unlikely(power == dac33->chip_power)) {
		dev_dbg(component->dev, "Trying to set the same power state: %s\n",
			power ? "ON" : "OFF");
		goto exit;
	}

	if (power) {
		ret = regulator_bulk_enable(ARRAY_SIZE(dac33->supplies),
					  dac33->supplies);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to enable supplies: %d\n", ret);
			goto exit;
		}

		if (dac33->power_gpio >= 0)
			gpio_set_value(dac33->power_gpio, 1);

		dac33->chip_power = 1;
	} else {
		dac33_soft_power(component, 0);
		if (dac33->power_gpio >= 0)
			gpio_set_value(dac33->power_gpio, 0);

		ret = regulator_bulk_disable(ARRAY_SIZE(dac33->supplies),
					     dac33->supplies);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to disable supplies: %d\n", ret);
			goto exit;
		}

		dac33->chip_power = 0;
	}

exit:
	mutex_unlock(&dac33->mutex);
	return ret;
}