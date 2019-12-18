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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct rt286_priv {int /*<<< orphan*/  regmap; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT286_IRQ_CTRL ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt286_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (struct snd_soc_jack*,int,int) ; 

int rt286_mic_detect(struct snd_soc_component *component, struct snd_soc_jack *jack)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct rt286_priv *rt286 = snd_soc_component_get_drvdata(component);

	rt286->jack = jack;

	if (jack) {
		/* enable IRQ */
		if (rt286->jack->status & SND_JACK_HEADPHONE)
			snd_soc_dapm_force_enable_pin(dapm, "LDO1");
		regmap_update_bits(rt286->regmap, RT286_IRQ_CTRL, 0x2, 0x2);
		/* Send an initial empty report */
		snd_soc_jack_report(rt286->jack, rt286->jack->status,
			SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);
	} else {
		/* disable IRQ */
		regmap_update_bits(rt286->regmap, RT286_IRQ_CTRL, 0x2, 0x0);
		snd_soc_dapm_disable_pin(dapm, "LDO1");
	}
	snd_soc_dapm_sync(dapm);

	return 0;
}