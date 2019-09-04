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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct nau8540 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8540_I2S_DO12_TRI ; 
 int /*<<< orphan*/  NAU8540_I2S_DO34_TRI ; 
 int /*<<< orphan*/  NAU8540_REG_PCM_CTRL1 ; 
 int /*<<< orphan*/  NAU8540_REG_PCM_CTRL2 ; 
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nau8540* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc_power_control(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *k, int  event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		msleep(300);
		/* DO12 and DO34 pad output enable */
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL1,
			NAU8540_I2S_DO12_TRI, 0);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL2,
			NAU8540_I2S_DO34_TRI, 0);
	} else if (SND_SOC_DAPM_EVENT_OFF(event)) {
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL1,
			NAU8540_I2S_DO12_TRI, NAU8540_I2S_DO12_TRI);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_PCM_CTRL2,
			NAU8540_I2S_DO34_TRI, NAU8540_I2S_DO34_TRI);
	}
	return 0;
}