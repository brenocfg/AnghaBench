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
 int /*<<< orphan*/  MT6351_AUDENC_ANA_CON9 ; 
 int RG_AUDMICBIAS0LOWPEN ; 
 int RG_AUDMICBIAS0VREF ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt_mic_bias_0_event(struct snd_soc_dapm_widget *w,
			       struct snd_kcontrol *kcontrol,
			       int event)
{
	struct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* MIC Bias 0 LowPower: 0_Normal */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x3 << RG_AUDMICBIAS0LOWPEN, 0x0);
		/* MISBIAS0 = 1P9V */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << RG_AUDMICBIAS0VREF,
				   0x2 << RG_AUDMICBIAS0VREF);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* MISBIAS0 = 1P97 */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << RG_AUDMICBIAS0VREF,
				   0x0 << RG_AUDMICBIAS0VREF);
		break;
	default:
		break;
	}
	return 0;
}