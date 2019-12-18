#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct snd_kcontrol {int dummy; } ;
struct arizona {int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_DVFS_ADSP1_RQ ; 
 unsigned int ARIZONA_SYSCLK_FREQ_MASK ; 
 unsigned int ARIZONA_SYSCLK_FREQ_SHIFT ; 
 int /*<<< orphan*/  ARIZONA_SYSTEM_CLOCK_1 ; 
 int EIO ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int arizona_dvfs_down (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int arizona_dvfs_up (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp2_set_dspclk (struct snd_soc_dapm_widget*,unsigned int) ; 
 int wm_adsp_early_event (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 

__attribute__((used)) static int wm5102_adsp_power_ev(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona *arizona = dev_get_drvdata(component->dev->parent);
	unsigned int v = 0;
	int ret;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		ret = regmap_read(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1, &v);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to read SYSCLK state: %d\n", ret);
			return -EIO;
		}

		v = (v & ARIZONA_SYSCLK_FREQ_MASK) >> ARIZONA_SYSCLK_FREQ_SHIFT;

		if (v >= 3) {
			ret = arizona_dvfs_up(component, ARIZONA_DVFS_ADSP1_RQ);
			if (ret) {
				dev_err(component->dev,
					"Failed to raise DVFS: %d\n", ret);
				return ret;
			}
		}

		wm_adsp2_set_dspclk(w, v);
		break;

	case SND_SOC_DAPM_POST_PMD:
		ret = arizona_dvfs_down(component, ARIZONA_DVFS_ADSP1_RQ);
		if (ret)
			dev_warn(component->dev,
				 "Failed to lower DVFS: %d\n", ret);
		break;

	default:
		break;
	}

	return wm_adsp_early_event(w, kcontrol, event);
}