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
struct snd_soc_jack {int status; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct es8316_priv {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; struct snd_soc_jack* jack; int /*<<< orphan*/  jd_inverted; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES8316_GPIO_DEBOUNCE ; 
 int /*<<< orphan*/  ES8316_GPIO_ENABLE_INTERRUPT ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es8316_enable_micbias_for_mic_gnd_short_detect (struct snd_soc_component*) ; 
 int /*<<< orphan*/  es8316_irq (int /*<<< orphan*/ ,struct es8316_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct es8316_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void es8316_enable_jack_detect(struct snd_soc_component *component,
				      struct snd_soc_jack *jack)
{
	struct es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	/*
	 * Init es8316->jd_inverted here and not in the probe, as we cannot
	 * guarantee that the bytchr-es8316 driver, which might set this
	 * property, will probe before us.
	 */
	es8316->jd_inverted = device_property_read_bool(component->dev,
							"everest,jack-detect-inverted");

	mutex_lock(&es8316->lock);

	es8316->jack = jack;

	if (es8316->jack->status & SND_JACK_MICROPHONE)
		es8316_enable_micbias_for_mic_gnd_short_detect(component);

	snd_soc_component_update_bits(component, ES8316_GPIO_DEBOUNCE,
				      ES8316_GPIO_ENABLE_INTERRUPT,
				      ES8316_GPIO_ENABLE_INTERRUPT);

	mutex_unlock(&es8316->lock);

	/* Enable irq and sync initial jack state */
	enable_irq(es8316->irq);
	es8316_irq(es8316->irq, es8316);
}