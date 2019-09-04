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
struct rt5659_priv {scalar_t__ jack_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5659_EJD_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_EJD_CTRL_2 ; 
 int /*<<< orphan*/  RT5659_PWR_ANLG_1 ; 
 int RT5659_PWR_FV2 ; 
 int RT5659_PWR_MB ; 
 int RT5659_PWR_VREF2 ; 
 scalar_t__ SND_JACK_HEADPHONE ; 
 scalar_t__ SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt5659_enable_push_button_irq (struct snd_soc_component*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt5659_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int rt5659_headset_detect(struct snd_soc_component *component, int jack_insert)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int val, i = 0, sleep_time[5] = {300, 150, 100, 50, 30};
	int reg_63;

	struct rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);

	if (jack_insert) {
		snd_soc_dapm_force_enable_pin(dapm,
			"Mic Det Power");
		snd_soc_dapm_sync(dapm);
		reg_63 = snd_soc_component_read32(component, RT5659_PWR_ANLG_1);

		snd_soc_component_update_bits(component, RT5659_PWR_ANLG_1,
			RT5659_PWR_VREF2 | RT5659_PWR_MB,
			RT5659_PWR_VREF2 | RT5659_PWR_MB);
		msleep(20);
		snd_soc_component_update_bits(component, RT5659_PWR_ANLG_1,
			RT5659_PWR_FV2, RT5659_PWR_FV2);

		snd_soc_component_write(component, RT5659_EJD_CTRL_2, 0x4160);
		snd_soc_component_update_bits(component, RT5659_EJD_CTRL_1,
			0x20, 0x0);
		msleep(20);
		snd_soc_component_update_bits(component, RT5659_EJD_CTRL_1,
			0x20, 0x20);

		while (i < 5) {
			msleep(sleep_time[i]);
			val = snd_soc_component_read32(component, RT5659_EJD_CTRL_2) & 0x0003;
			i++;
			if (val == 0x1 || val == 0x2 || val == 0x3)
				break;
		}

		switch (val) {
		case 1:
			rt5659->jack_type = SND_JACK_HEADSET;
			rt5659_enable_push_button_irq(component, true);
			break;
		default:
			snd_soc_component_write(component, RT5659_PWR_ANLG_1, reg_63);
			rt5659->jack_type = SND_JACK_HEADPHONE;
			snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
			snd_soc_dapm_sync(dapm);
			break;
		}
	} else {
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		if (rt5659->jack_type == SND_JACK_HEADSET)
			rt5659_enable_push_button_irq(component, false);
		rt5659->jack_type = 0;
	}

	dev_dbg(component->dev, "jack_type = %d\n", rt5659->jack_type);
	return rt5659->jack_type;
}