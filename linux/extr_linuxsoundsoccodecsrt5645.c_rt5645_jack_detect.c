#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_context {TYPE_1__* card; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ jd_mode; scalar_t__ level_trigger_irq; } ;
struct rt5645_priv {int jack_type; int /*<<< orphan*/  regmap; TYPE_2__ pdata; scalar_t__ en_button_func; } ;
struct TYPE_3__ {int /*<<< orphan*/  instantiated; } ;

/* Variables and functions */
 int RT5645_CBJ_BST1_EN ; 
 int RT5645_CBJ_MN_JD ; 
 int /*<<< orphan*/  RT5645_CHARGE_PUMP ; 
 int /*<<< orphan*/  RT5645_HP_VOL ; 
 int /*<<< orphan*/  RT5645_IN1_CTRL1 ; 
 int /*<<< orphan*/  RT5645_IN1_CTRL2 ; 
 int /*<<< orphan*/  RT5645_IN1_CTRL3 ; 
 int /*<<< orphan*/  RT5645_IRQ_CTRL2 ; 
 int RT5645_JD_1_1_INV ; 
 int RT5645_JD_1_1_MASK ; 
 int RT5645_JD_1_1_NOR ; 
 int /*<<< orphan*/  RT5645_JD_CTRL3 ; 
 int RT5645_L_MUTE ; 
 int /*<<< orphan*/  RT5645_PWR_ANLG1 ; 
 int RT5645_PWR_LDO2 ; 
 int RT5645_PWR_MB ; 
 int RT5645_PWR_MIC_DET ; 
 int /*<<< orphan*/  RT5645_PWR_MIXER ; 
 int /*<<< orphan*/  RT5645_PWR_VOL ; 
 int RT5645_PWR_VREF2 ; 
 int RT5645_R_MUTE ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt5645_enable_push_button_irq (struct snd_soc_component*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int rt5645_jack_detect(struct snd_soc_component *component, int jack_insert)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	if (jack_insert) {
		regmap_write(rt5645->regmap, RT5645_CHARGE_PUMP, 0x0e06);

		/* for jack type detect */
		snd_soc_dapm_force_enable_pin(dapm, "LDO2");
		snd_soc_dapm_force_enable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		if (!dapm->card->instantiated) {
			/* Power up necessary bits for JD if dapm is
			   not ready yet */
			regmap_update_bits(rt5645->regmap, RT5645_PWR_ANLG1,
				RT5645_PWR_MB | RT5645_PWR_VREF2,
				RT5645_PWR_MB | RT5645_PWR_VREF2);
			regmap_update_bits(rt5645->regmap, RT5645_PWR_MIXER,
				RT5645_PWR_LDO2, RT5645_PWR_LDO2);
			regmap_update_bits(rt5645->regmap, RT5645_PWR_VOL,
				RT5645_PWR_MIC_DET, RT5645_PWR_MIC_DET);
		}

		regmap_write(rt5645->regmap, RT5645_JD_CTRL3, 0x00f0);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2,
			RT5645_CBJ_MN_JD, RT5645_CBJ_MN_JD);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL1,
			RT5645_CBJ_BST1_EN, RT5645_CBJ_BST1_EN);
		msleep(100);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2,
			RT5645_CBJ_MN_JD, 0);

		msleep(600);
		regmap_read(rt5645->regmap, RT5645_IN1_CTRL3, &val);
		val &= 0x7;
		dev_dbg(component->dev, "val = %d\n", val);

		if (val == 1 || val == 2) {
			rt5645->jack_type = SND_JACK_HEADSET;
			if (rt5645->en_button_func) {
				rt5645_enable_push_button_irq(component, true);
			}
		} else {
			snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
			snd_soc_dapm_sync(dapm);
			rt5645->jack_type = SND_JACK_HEADPHONE;
		}
		if (rt5645->pdata.level_trigger_irq)
			regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				RT5645_JD_1_1_MASK, RT5645_JD_1_1_NOR);
	} else { /* jack out */
		rt5645->jack_type = 0;

		regmap_update_bits(rt5645->regmap, RT5645_HP_VOL,
			RT5645_L_MUTE | RT5645_R_MUTE,
			RT5645_L_MUTE | RT5645_R_MUTE);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2,
			RT5645_CBJ_MN_JD, RT5645_CBJ_MN_JD);
		regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL1,
			RT5645_CBJ_BST1_EN, 0);

		if (rt5645->en_button_func)
			rt5645_enable_push_button_irq(component, false);

		if (rt5645->pdata.jd_mode == 0)
			snd_soc_dapm_disable_pin(dapm, "LDO2");
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
		if (rt5645->pdata.level_trigger_irq)
			regmap_update_bits(rt5645->regmap, RT5645_IRQ_CTRL2,
				RT5645_JD_1_1_MASK, RT5645_JD_1_1_INV);
	}

	return rt5645->jack_type;
}