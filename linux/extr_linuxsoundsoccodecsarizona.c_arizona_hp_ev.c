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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct arizona_priv {struct arizona* arizona; } ;
struct arizona {unsigned int hp_ena; int /*<<< orphan*/  regmap; scalar_t__ hpdet_clamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_OUTPUT_ENABLES_1 ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int arizona_out_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 
 int /*<<< orphan*/  regmap_update_bits_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int arizona_hp_ev(struct snd_soc_dapm_widget *w, struct snd_kcontrol *kcontrol,
		  int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	unsigned int mask = 1 << w->shift;
	unsigned int val;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		val = mask;
		break;
	case SND_SOC_DAPM_PRE_PMD:
		val = 0;
		break;
	case SND_SOC_DAPM_PRE_PMU:
	case SND_SOC_DAPM_POST_PMD:
		return arizona_out_ev(w, kcontrol, event);
	default:
		return -EINVAL;
	}

	/* Store the desired state for the HP outputs */
	priv->arizona->hp_ena &= ~mask;
	priv->arizona->hp_ena |= val;

	/* Force off if HPDET clamp is active */
	if (priv->arizona->hpdet_clamp)
		val = 0;

	regmap_update_bits_async(arizona->regmap, ARIZONA_OUTPUT_ENABLES_1,
				 mask, val);

	return arizona_out_ev(w, kcontrol, event);
}