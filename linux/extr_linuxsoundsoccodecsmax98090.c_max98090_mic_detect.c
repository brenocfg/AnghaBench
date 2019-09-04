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
struct max98090_priv {int /*<<< orphan*/  jack_work; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98090_IJDET_MASK ; 
 int M98090_IJDET_SHIFT ; 
 int /*<<< orphan*/  M98090_REG_INTERRUPT_S ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_jack_report (struct snd_soc_jack*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

int max98090_mic_detect(struct snd_soc_component *component,
	struct snd_soc_jack *jack)
{
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "max98090_mic_detect\n");

	max98090->jack = jack;
	if (jack) {
		snd_soc_component_update_bits(component, M98090_REG_INTERRUPT_S,
			M98090_IJDET_MASK,
			1 << M98090_IJDET_SHIFT);
	} else {
		snd_soc_component_update_bits(component, M98090_REG_INTERRUPT_S,
			M98090_IJDET_MASK,
			0);
	}

	/* Send an initial empty report */
	snd_soc_jack_report(max98090->jack, 0,
			    SND_JACK_HEADSET | SND_JACK_BTN_0);

	queue_delayed_work(system_power_efficient_wq,
			   &max98090->jack_work,
			   msecs_to_jiffies(100));

	return 0;
}