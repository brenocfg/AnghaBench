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
struct regmap {int dummy; } ;
struct aud96p22_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD96P22_RESET ; 
 int EINVAL ; 
 int /*<<< orphan*/  RST_ADC_DPZ ; 
 int SND_SOC_DAPM_POST_PMU ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aud96p22_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aud96p22_adc_event(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct aud96p22_priv *priv = snd_soc_component_get_drvdata(component);
	struct regmap *regmap = priv->regmap;

	if (event != SND_SOC_DAPM_POST_PMU)
		return -EINVAL;

	/* Assert/de-assert the bit to reset ADC data path  */
	regmap_update_bits(regmap, AUD96P22_RESET, RST_ADC_DPZ, 0);
	regmap_update_bits(regmap, AUD96P22_RESET, RST_ADC_DPZ, RST_ADC_DPZ);

	return 0;
}