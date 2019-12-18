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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dapm_widget {int reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_HP_L_AMP_MIN_GAIN_EN_MASK ; 
 int /*<<< orphan*/  DA7219_HP_L_CTRL ; 
 int /*<<< orphan*/  DA7219_HP_R_AMP_MIN_GAIN_EN_MASK ; 
 int /*<<< orphan*/  DA7219_HP_R_CTRL ; 
 int /*<<< orphan*/  DA7219_MIN_GAIN_DELAY ; 
#define  DA7219_MIXOUT_L_CTRL 131 
#define  DA7219_MIXOUT_R_CTRL 130 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7219_mixout_event(struct snd_soc_dapm_widget *w,
			       struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 hp_ctrl, min_gain_mask;

	switch (w->reg) {
	case DA7219_MIXOUT_L_CTRL:
		hp_ctrl = DA7219_HP_L_CTRL;
		min_gain_mask = DA7219_HP_L_AMP_MIN_GAIN_EN_MASK;
		break;
	case DA7219_MIXOUT_R_CTRL:
		hp_ctrl = DA7219_HP_R_CTRL;
		min_gain_mask = DA7219_HP_R_AMP_MIN_GAIN_EN_MASK;
		break;
	default:
		return -EINVAL;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMD:
		/* Enable minimum gain on HP to avoid pops */
		snd_soc_component_update_bits(component, hp_ctrl, min_gain_mask,
				    min_gain_mask);

		msleep(DA7219_MIN_GAIN_DELAY);

		break;
	case SND_SOC_DAPM_POST_PMU:
		/* Remove minimum gain on HP */
		snd_soc_component_update_bits(component, hp_ctrl, min_gain_mask, 0);

		break;
	}

	return 0;
}