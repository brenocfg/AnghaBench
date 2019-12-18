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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct rt298_priv {struct snd_soc_jack* jack; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT298_IRQ_CTRL ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rt298_jack_detect (struct rt298_priv*,int*,int*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt298_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (struct snd_soc_jack*,int,int) ; 

int rt298_mic_detect(struct snd_soc_component *component, struct snd_soc_jack *jack)
{
	struct rt298_priv *rt298 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm;
	bool hp = false;
	bool mic = false;
	int status = 0;

	/* If jack in NULL, disable HS jack */
	if (!jack) {
		regmap_update_bits(rt298->regmap, RT298_IRQ_CTRL, 0x2, 0x0);
		dapm = snd_soc_component_get_dapm(component);
		snd_soc_dapm_disable_pin(dapm, "LDO1");
		snd_soc_dapm_sync(dapm);
		return 0;
	}

	rt298->jack = jack;
	regmap_update_bits(rt298->regmap, RT298_IRQ_CTRL, 0x2, 0x2);

	rt298_jack_detect(rt298, &hp, &mic);
	if (hp)
		status |= SND_JACK_HEADPHONE;

	if (mic)
		status |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(rt298->jack, status,
		SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);

	return 0;
}