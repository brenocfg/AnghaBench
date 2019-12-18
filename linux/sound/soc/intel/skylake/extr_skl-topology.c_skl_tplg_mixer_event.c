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
struct snd_soc_dapm_widget {struct snd_soc_dapm_context* dapm; } ;
struct snd_soc_dapm_context {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct skl_dev {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 struct skl_dev* get_skl_ctx (int /*<<< orphan*/ ) ; 
 int skl_tplg_mixer_dapm_post_pmd_event (struct snd_soc_dapm_widget*,struct skl_dev*) ; 
 int skl_tplg_mixer_dapm_post_pmu_event (struct snd_soc_dapm_widget*,struct skl_dev*) ; 
 int skl_tplg_mixer_dapm_pre_pmd_event (struct snd_soc_dapm_widget*,struct skl_dev*) ; 
 int skl_tplg_mixer_dapm_pre_pmu_event (struct snd_soc_dapm_widget*,struct skl_dev*) ; 

__attribute__((used)) static int skl_tplg_mixer_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *k, int event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct skl_dev *skl = get_skl_ctx(dapm->dev);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		return skl_tplg_mixer_dapm_pre_pmu_event(w, skl);

	case SND_SOC_DAPM_POST_PMU:
		return skl_tplg_mixer_dapm_post_pmu_event(w, skl);

	case SND_SOC_DAPM_PRE_PMD:
		return skl_tplg_mixer_dapm_pre_pmd_event(w, skl);

	case SND_SOC_DAPM_POST_PMD:
		return skl_tplg_mixer_dapm_post_pmd_event(w, skl);
	}

	return 0;
}