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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct arizona_priv {int out_up_delay; int out_down_delay; int /*<<< orphan*/  out_down_pending; int /*<<< orphan*/  out_up_pending; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  ARIZONA_OUT1L_ENA_SHIFT 143 
#define  ARIZONA_OUT1R_ENA_SHIFT 142 
#define  ARIZONA_OUT2L_ENA_SHIFT 141 
#define  ARIZONA_OUT2R_ENA_SHIFT 140 
#define  ARIZONA_OUT3L_ENA_SHIFT 139 
#define  ARIZONA_OUT3R_ENA_SHIFT 138 
#define  ARIZONA_OUT4L_ENA_SHIFT 137 
#define  ARIZONA_OUT4R_ENA_SHIFT 136 
#define  SND_SOC_DAPM_POST_PMD 135 
#define  SND_SOC_DAPM_POST_PMU 134 
#define  SND_SOC_DAPM_PRE_PMD 133 
#define  SND_SOC_DAPM_PRE_PMU 132 
#define  WM1814 131 
#define  WM5102 130 
#define  WM8997 129 
#define  WM8998 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int arizona_out_ev(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol,
		   int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		switch (w->shift) {
		case ARIZONA_OUT1L_ENA_SHIFT:
		case ARIZONA_OUT1R_ENA_SHIFT:
		case ARIZONA_OUT2L_ENA_SHIFT:
		case ARIZONA_OUT2R_ENA_SHIFT:
		case ARIZONA_OUT3L_ENA_SHIFT:
		case ARIZONA_OUT3R_ENA_SHIFT:
			priv->out_up_pending++;
			priv->out_up_delay += 17;
			break;
		case ARIZONA_OUT4L_ENA_SHIFT:
		case ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_up_pending++;
			switch (arizona->type) {
			case WM5102:
			case WM8997:
				break;
			default:
				priv->out_up_delay += 10;
				break;
			}
			break;
		default:
			break;
		}
		break;
	case SND_SOC_DAPM_POST_PMU:
		switch (w->shift) {
		case ARIZONA_OUT1L_ENA_SHIFT:
		case ARIZONA_OUT1R_ENA_SHIFT:
		case ARIZONA_OUT2L_ENA_SHIFT:
		case ARIZONA_OUT2R_ENA_SHIFT:
		case ARIZONA_OUT3L_ENA_SHIFT:
		case ARIZONA_OUT3R_ENA_SHIFT:
		case ARIZONA_OUT4L_ENA_SHIFT:
		case ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_up_pending--;
			if (!priv->out_up_pending && priv->out_up_delay) {
				dev_dbg(component->dev, "Power up delay: %d\n",
					priv->out_up_delay);
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
		case ARIZONA_OUT1L_ENA_SHIFT:
		case ARIZONA_OUT1R_ENA_SHIFT:
		case ARIZONA_OUT2L_ENA_SHIFT:
		case ARIZONA_OUT2R_ENA_SHIFT:
		case ARIZONA_OUT3L_ENA_SHIFT:
		case ARIZONA_OUT3R_ENA_SHIFT:
			priv->out_down_pending++;
			priv->out_down_delay++;
			break;
		case ARIZONA_OUT4L_ENA_SHIFT:
		case ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_down_pending++;
			switch (arizona->type) {
			case WM5102:
			case WM8997:
				break;
			case WM8998:
			case WM1814:
				priv->out_down_delay += 5;
				break;
			default:
				priv->out_down_delay++;
				break;
			}
		default:
			break;
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		switch (w->shift) {
		case ARIZONA_OUT1L_ENA_SHIFT:
		case ARIZONA_OUT1R_ENA_SHIFT:
		case ARIZONA_OUT2L_ENA_SHIFT:
		case ARIZONA_OUT2R_ENA_SHIFT:
		case ARIZONA_OUT3L_ENA_SHIFT:
		case ARIZONA_OUT3R_ENA_SHIFT:
		case ARIZONA_OUT4L_ENA_SHIFT:
		case ARIZONA_OUT4R_ENA_SHIFT:
			priv->out_down_pending--;
			if (!priv->out_down_pending && priv->out_down_delay) {
				dev_dbg(component->dev, "Power down delay: %d\n",
					priv->out_down_delay);
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