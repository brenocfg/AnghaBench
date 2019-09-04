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
typedef  int u8 ;
struct snd_soc_dapm_widget {int reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct da7218_priv {int in_filt_en; int mic_lvl_det_en; } ;

/* Variables and functions */
#define  DA7218_IN_1L_FILTER_CTRL 133 
#define  DA7218_IN_1R_FILTER_CTRL 132 
#define  DA7218_IN_2L_FILTER_CTRL 131 
#define  DA7218_IN_2R_FILTER_CTRL 130 
 int /*<<< orphan*/  DA7218_LVL_DET_CTRL ; 
 int DA7218_LVL_DET_EN_CHAN1L_SHIFT ; 
 int DA7218_LVL_DET_EN_CHAN1R_SHIFT ; 
 int DA7218_LVL_DET_EN_CHAN2L_SHIFT ; 
 int DA7218_LVL_DET_EN_CHAN2R_SHIFT ; 
 int /*<<< orphan*/  DA7218_MIC_LVL_DET_DELAY ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7218_in_filter_event(struct snd_soc_dapm_widget *w,
				  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	u8 mask;

	switch (w->reg) {
	case DA7218_IN_1L_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN1L_SHIFT);
		break;
	case DA7218_IN_1R_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN1R_SHIFT);
		break;
	case DA7218_IN_2L_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN2L_SHIFT);
		break;
	case DA7218_IN_2R_FILTER_CTRL:
		mask = (1 << DA7218_LVL_DET_EN_CHAN2R_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		da7218->in_filt_en |= mask;
		/*
		 * If we're enabling path for mic level detect, wait for path
		 * to settle before enabling feature to avoid incorrect and
		 * unwanted detect events.
		 */
		if (mask & da7218->mic_lvl_det_en)
			msleep(DA7218_MIC_LVL_DET_DELAY);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		da7218->in_filt_en &= ~mask;
		break;
	default:
		return -EINVAL;
	}

	/* Enable configured level detection paths */
	snd_soc_component_write(component, DA7218_LVL_DET_CTRL,
		      (da7218->in_filt_en & da7218->mic_lvl_det_en));

	return 0;
}