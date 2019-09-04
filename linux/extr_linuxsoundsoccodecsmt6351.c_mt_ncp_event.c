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
struct snd_soc_component {int /*<<< orphan*/  regmap; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT6351_AFE_NCP_CFG0 ; 
 int /*<<< orphan*/  MT6351_AFE_NCP_CFG1 ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mt_ncp_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol,
			int event)
{
	struct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_NCP_CFG1,
				   0xffff, 0x1515);
		/* NCP: ck1 and ck2 clock frequecy adjust configure */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_NCP_CFG0,
				   0xfffe, 0x8C00);
		break;
	case SND_SOC_DAPM_POST_PMU:
		usleep_range(250, 270);
		break;
	default:
		break;
	}

	return 0;
}