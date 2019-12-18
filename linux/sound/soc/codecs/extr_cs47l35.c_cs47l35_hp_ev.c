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
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  cs47l35_hp_post_disable (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  cs47l35_hp_post_enable (struct snd_soc_dapm_widget*) ; 
 int madera_hp_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 

__attribute__((used)) static int cs47l35_hp_ev(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	int ret;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
	case SND_SOC_DAPM_PRE_PMD:
		return madera_hp_ev(w, kcontrol, event);
	case SND_SOC_DAPM_POST_PMU:
		ret = madera_hp_ev(w, kcontrol, event);
		if (ret < 0)
			return ret;

		cs47l35_hp_post_enable(w);
		return 0;
	case SND_SOC_DAPM_POST_PMD:
		ret = madera_hp_ev(w, kcontrol, event);
		cs47l35_hp_post_disable(w);
		return ret;
	default:
		return -EINVAL;
	}
}