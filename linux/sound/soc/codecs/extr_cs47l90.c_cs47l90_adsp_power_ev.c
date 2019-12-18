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
struct snd_soc_dapm_widget {int /*<<< orphan*/  shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct madera_priv {struct madera* madera; } ;
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct cs47l90 {struct madera_priv core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_DSP_CLOCK_2 ; 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int madera_set_adsp_clk (struct madera_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct cs47l90* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int wm_adsp_early_event (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 

__attribute__((used)) static int cs47l90_adsp_power_ev(struct snd_soc_dapm_widget *w,
				 struct snd_kcontrol *kcontrol,
				 int event)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	struct cs47l90 *cs47l90 = snd_soc_component_get_drvdata(component);
	struct madera_priv *priv = &cs47l90->core;
	struct madera *madera = priv->madera;
	unsigned int freq;
	int ret;

	ret = regmap_read(madera->regmap, MADERA_DSP_CLOCK_2, &freq);
	if (ret != 0) {
		dev_err(madera->dev,
			"Failed to read MADERA_DSP_CLOCK_2: %d\n", ret);
		return ret;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		ret = madera_set_adsp_clk(&cs47l90->core, w->shift, freq);
		if (ret)
			return ret;
		break;
	default:
		break;
	}

	return wm_adsp_early_event(w, kcontrol, event);
}