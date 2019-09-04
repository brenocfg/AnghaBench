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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5668_priv {int jack_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5668_CBJ_CTRL_1 ; 
 int /*<<< orphan*/  RT5668_CBJ_CTRL_2 ; 
 unsigned int RT5668_JACK_TYPE_MASK ; 
 int /*<<< orphan*/  RT5668_TRIG_JD_HIGH ; 
 int /*<<< orphan*/  RT5668_TRIG_JD_LOW ; 
 int /*<<< orphan*/  RT5668_TRIG_JD_MASK ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rt5668_enable_push_button_irq (struct snd_soc_component*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt5668_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5668_headset_detect(struct snd_soc_component *component,
		int jack_insert)
{
	struct rt5668_priv *rt5668 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	unsigned int val, count;

	if (jack_insert) {
		snd_soc_dapm_force_enable_pin(dapm, "CBJ Power");
		snd_soc_dapm_sync(dapm);
		snd_soc_component_update_bits(component, RT5668_CBJ_CTRL_1,
			RT5668_TRIG_JD_MASK, RT5668_TRIG_JD_HIGH);

		count = 0;
		val = snd_soc_component_read32(component, RT5668_CBJ_CTRL_2)
			& RT5668_JACK_TYPE_MASK;
		while (val == 0 && count < 50) {
			usleep_range(10000, 15000);
			val = snd_soc_component_read32(component,
				RT5668_CBJ_CTRL_2) & RT5668_JACK_TYPE_MASK;
			count++;
		}

		switch (val) {
		case 0x1:
		case 0x2:
			rt5668->jack_type = SND_JACK_HEADSET;
			rt5668_enable_push_button_irq(component, true);
			break;
		default:
			rt5668->jack_type = SND_JACK_HEADPHONE;
		}

	} else {
		rt5668_enable_push_button_irq(component, false);
		snd_soc_component_update_bits(component, RT5668_CBJ_CTRL_1,
			RT5668_TRIG_JD_MASK, RT5668_TRIG_JD_LOW);
		snd_soc_dapm_disable_pin(dapm, "CBJ Power");
		snd_soc_dapm_sync(dapm);

		rt5668->jack_type = 0;
	}

	dev_dbg(component->dev, "jack_type = %d\n", rt5668->jack_type);
	return rt5668->jack_type;
}