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
struct madera_priv {struct madera* madera; } ;
struct madera {unsigned int hp_ena; int type; int /*<<< orphan*/  regmap; scalar_t__* out_shorted; int /*<<< orphan*/ * out_clamp; } ;

/* Variables and functions */
#define  CS42L92 134 
#define  CS47L92 133 
#define  CS47L93 132 
 unsigned int MADERA_EP_SEL_MASK ; 
 int /*<<< orphan*/  MADERA_OUTPUT_ENABLES_1 ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int madera_out_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int madera_hp_ev(struct snd_soc_dapm_widget *w,
		 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	unsigned int mask = 1 << w->shift;
	unsigned int out_num = w->shift / 2;
	unsigned int val;
	unsigned int ep_sel = 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		val = mask;
		break;
	case SND_SOC_DAPM_PRE_PMD:
		val = 0;
		break;
	case SND_SOC_DAPM_PRE_PMU:
	case SND_SOC_DAPM_POST_PMD:
		return madera_out_ev(w, kcontrol, event);
	default:
		return 0;
	}

	/* Store the desired state for the HP outputs */
	madera->hp_ena &= ~mask;
	madera->hp_ena |= val;

	switch (madera->type) {
	case CS42L92:
	case CS47L92:
	case CS47L93:
		break;
	default:
		/* if OUT1 is routed to EPOUT, ignore HP clamp and impedance */
		regmap_read(madera->regmap, MADERA_OUTPUT_ENABLES_1, &ep_sel);
		ep_sel &= MADERA_EP_SEL_MASK;
		break;
	}

	/* Force off if HPDET has disabled the clamp for this output */
	if (!ep_sel &&
	    (!madera->out_clamp[out_num] || madera->out_shorted[out_num]))
		val = 0;

	regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1, mask, val);

	return madera_out_ev(w, kcontrol, event);
}