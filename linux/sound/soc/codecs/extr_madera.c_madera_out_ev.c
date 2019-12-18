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
struct madera_priv {int out_up_delay; int out_down_delay; int /*<<< orphan*/  out_down_pending; int /*<<< orphan*/  out_up_pending; struct madera* madera; } ;
struct madera {int type; } ;

/* Variables and functions */
#define  CS42L92 142 
#define  CS47L90 141 
#define  CS47L91 140 
#define  CS47L92 139 
#define  CS47L93 138 
#define  MADERA_OUT1L_ENA_SHIFT 137 
#define  MADERA_OUT1R_ENA_SHIFT 136 
#define  MADERA_OUT2L_ENA_SHIFT 135 
#define  MADERA_OUT2R_ENA_SHIFT 134 
#define  MADERA_OUT3L_ENA_SHIFT 133 
#define  MADERA_OUT3R_ENA_SHIFT 132 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  msleep (int) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int madera_out_ev(struct snd_soc_dapm_widget *w,
		  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	int out_up_delay;

	switch (madera->type) {
	case CS47L90:
	case CS47L91:
	case CS42L92:
	case CS47L92:
	case CS47L93:
		out_up_delay = 6;
		break;
	default:
		out_up_delay = 17;
		break;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		switch (w->shift) {
		case MADERA_OUT1L_ENA_SHIFT:
		case MADERA_OUT1R_ENA_SHIFT:
		case MADERA_OUT2L_ENA_SHIFT:
		case MADERA_OUT2R_ENA_SHIFT:
		case MADERA_OUT3L_ENA_SHIFT:
		case MADERA_OUT3R_ENA_SHIFT:
			priv->out_up_pending++;
			priv->out_up_delay += out_up_delay;
			break;
		default:
			break;
		}
		break;

	case SND_SOC_DAPM_POST_PMU:
		switch (w->shift) {
		case MADERA_OUT1L_ENA_SHIFT:
		case MADERA_OUT1R_ENA_SHIFT:
		case MADERA_OUT2L_ENA_SHIFT:
		case MADERA_OUT2R_ENA_SHIFT:
		case MADERA_OUT3L_ENA_SHIFT:
		case MADERA_OUT3R_ENA_SHIFT:
			priv->out_up_pending--;
			if (!priv->out_up_pending) {
				msleep(priv->out_up_delay);
				priv->out_up_delay = 0;
			}
			break;

		default:
			break;
		}
		break;

	case SND_SOC_DAPM_PRE_PMD:
		switch (w->shift) {
		case MADERA_OUT1L_ENA_SHIFT:
		case MADERA_OUT1R_ENA_SHIFT:
		case MADERA_OUT2L_ENA_SHIFT:
		case MADERA_OUT2R_ENA_SHIFT:
		case MADERA_OUT3L_ENA_SHIFT:
		case MADERA_OUT3R_ENA_SHIFT:
			priv->out_down_pending++;
			priv->out_down_delay++;
			break;
		default:
			break;
		}
		break;

	case SND_SOC_DAPM_POST_PMD:
		switch (w->shift) {
		case MADERA_OUT1L_ENA_SHIFT:
		case MADERA_OUT1R_ENA_SHIFT:
		case MADERA_OUT2L_ENA_SHIFT:
		case MADERA_OUT2R_ENA_SHIFT:
		case MADERA_OUT3L_ENA_SHIFT:
		case MADERA_OUT3R_ENA_SHIFT:
			priv->out_down_pending--;
			if (!priv->out_down_pending) {
				msleep(priv->out_down_delay);
				priv->out_down_delay = 0;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}