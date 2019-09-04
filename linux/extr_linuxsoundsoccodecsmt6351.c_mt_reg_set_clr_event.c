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
struct snd_soc_dapm_widget {int reg; int shift; int /*<<< orphan*/  off_val; int /*<<< orphan*/  on_val; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  regmap; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int REG_STRIDE ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt_reg_set_clr_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol,
				int event)
{
	struct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (w->on_val) {
			/* SET REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE,
					   0x1 << w->shift,
					   0x1 << w->shift);
		} else {
			/* CLR REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE * 2,
					   0x1 << w->shift,
					   0x1 << w->shift);
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		if (w->off_val) {
			/* SET REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE,
					   0x1 << w->shift,
					   0x1 << w->shift);
		} else {
			/* CLR REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE * 2,
					   0x1 << w->shift,
					   0x1 << w->shift);
		}
		break;
	default:
		break;
	}

	return 0;
}