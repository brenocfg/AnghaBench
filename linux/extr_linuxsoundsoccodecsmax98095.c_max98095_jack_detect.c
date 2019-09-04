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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98095_priv {struct snd_soc_jack* mic_jack; struct snd_soc_jack* headphone_jack; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M98095_013_JACK_INT_EN ; 
 int /*<<< orphan*/  M98095_IDDONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  max98095_jack_detect_enable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  max98095_report_jack (int /*<<< orphan*/ ,struct snd_soc_component*) ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

int max98095_jack_detect(struct snd_soc_component *component,
	struct snd_soc_jack *hp_jack, struct snd_soc_jack *mic_jack)
{
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	struct i2c_client *client = to_i2c_client(component->dev);
	int ret = 0;

	max98095->headphone_jack = hp_jack;
	max98095->mic_jack = mic_jack;

	/* only progress if we have at least 1 jack pointer */
	if (!hp_jack && !mic_jack)
		return -EINVAL;

	max98095_jack_detect_enable(component);

	/* enable interrupts for headphone jack detection */
	ret = snd_soc_component_update_bits(component, M98095_013_JACK_INT_EN,
		M98095_IDDONE, M98095_IDDONE);
	if (ret < 0) {
		dev_err(component->dev, "Failed to cfg jack irqs %d\n", ret);
		return ret;
	}

	max98095_report_jack(client->irq, component);
	return 0;
}