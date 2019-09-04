#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int sar_hs_type; } ;
struct rt5665_priv {int sar_adc_value; scalar_t__ jack_type; int /*<<< orphan*/  regmap; TYPE_1__ pdata; int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5665_EJD_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_EJD_CTRL_3 ; 
 int /*<<< orphan*/  RT5665_GPIO_STA ; 
 int /*<<< orphan*/  RT5665_IL_CMD_1 ; 
 int /*<<< orphan*/  RT5665_MICBIAS_2 ; 
 int /*<<< orphan*/  RT5665_SAR_IL_CMD_1 ; 
 int /*<<< orphan*/  RT5665_SAR_IL_CMD_4 ; 
 scalar_t__ SND_JACK_HEADPHONE ; 
 scalar_t__ SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt5665_enable_push_button_irq (struct snd_soc_component*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt5665_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5665_headset_detect(struct snd_soc_component *component, int jack_insert)
{
	struct rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	unsigned int sar_hs_type, val;

	if (jack_insert) {
		snd_soc_dapm_force_enable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_sync(dapm);

		regmap_update_bits(rt5665->regmap, RT5665_MICBIAS_2, 0x100,
			0x100);

		regmap_read(rt5665->regmap, RT5665_GPIO_STA, &val);
		if (val & 0x4) {
			regmap_update_bits(rt5665->regmap, RT5665_EJD_CTRL_1,
				0x100, 0);

			regmap_read(rt5665->regmap, RT5665_GPIO_STA, &val);
			while (val & 0x4) {
				usleep_range(10000, 15000);
				regmap_read(rt5665->regmap, RT5665_GPIO_STA,
					&val);
			}
		}

		regmap_update_bits(rt5665->regmap, RT5665_EJD_CTRL_1,
			0x1a0, 0x120);
		regmap_write(rt5665->regmap, RT5665_EJD_CTRL_3, 0x3424);
		regmap_write(rt5665->regmap, RT5665_IL_CMD_1, 0x0048);
		regmap_write(rt5665->regmap, RT5665_SAR_IL_CMD_1, 0xa291);

		usleep_range(10000, 15000);

		rt5665->sar_adc_value = snd_soc_component_read32(rt5665->component,
			RT5665_SAR_IL_CMD_4) & 0x7ff;

		sar_hs_type = rt5665->pdata.sar_hs_type ?
			rt5665->pdata.sar_hs_type : 729;

		if (rt5665->sar_adc_value > sar_hs_type) {
			rt5665->jack_type = SND_JACK_HEADSET;
			rt5665_enable_push_button_irq(component, true);
			} else {
			rt5665->jack_type = SND_JACK_HEADPHONE;
			regmap_write(rt5665->regmap, RT5665_SAR_IL_CMD_1,
				0x2291);
			regmap_update_bits(rt5665->regmap, RT5665_MICBIAS_2,
				0x100, 0);
			snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
			snd_soc_dapm_sync(dapm);
		}
	} else {
		regmap_write(rt5665->regmap, RT5665_SAR_IL_CMD_1, 0x2291);
		regmap_update_bits(rt5665->regmap, RT5665_MICBIAS_2, 0x100, 0);
		snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_sync(dapm);
		if (rt5665->jack_type == SND_JACK_HEADSET)
			rt5665_enable_push_button_irq(component, false);
		rt5665->jack_type = 0;
	}

	dev_dbg(component->dev, "jack_type = %d\n", rt5665->jack_type);
	return rt5665->jack_type;
}