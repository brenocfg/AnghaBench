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
struct arizona_priv {int dvfs_cached; int /*<<< orphan*/  dvfs_lock; int /*<<< orphan*/  dvfs_reqs; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int arizona_dvfs_disable (struct snd_soc_component*) ; 
 int arizona_dvfs_enable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int arizona_dvfs_sysclk_ev(struct snd_soc_dapm_widget *w,
			   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	int ret = 0;

	mutex_lock(&priv->dvfs_lock);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (priv->dvfs_reqs)
			ret = arizona_dvfs_enable(component);

		priv->dvfs_cached = false;
		break;
	case SND_SOC_DAPM_PRE_PMD:
		/* We must ensure DVFS is disabled before the codec goes into
		 * suspend so that we are never in an illegal state of DVFS
		 * enabled without enough DCVDD
		 */
		priv->dvfs_cached = true;

		if (priv->dvfs_reqs)
			ret = arizona_dvfs_disable(component);
		break;
	default:
		break;
	}

	mutex_unlock(&priv->dvfs_lock);
	return ret;
}