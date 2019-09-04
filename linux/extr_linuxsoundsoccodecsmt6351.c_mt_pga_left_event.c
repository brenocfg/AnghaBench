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
 int /*<<< orphan*/  MT6351_AUDENC_ANA_CON0 ; 
 int RG_AUDPREAMPLDCCEN ; 
 int RG_AUDPREAMPLDCPRECHARGE ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mt_pga_left_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol,
			     int event)
{
	struct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Audio L PGA precharge on */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << RG_AUDPREAMPLDCPRECHARGE,
				   0x1 << RG_AUDPREAMPLDCPRECHARGE);
		/* Audio L PGA mode: 1_DCC */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << RG_AUDPREAMPLDCCEN,
				   0x1 << RG_AUDPREAMPLDCCEN);
		break;
	case SND_SOC_DAPM_POST_PMU:
		usleep_range(100, 120);
		/* Audio L PGA precharge off */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << RG_AUDPREAMPLDCPRECHARGE,
				   0x0 << RG_AUDPREAMPLDCPRECHARGE);
		break;
	default:
		break;
	}
	return 0;
}