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
struct regmap {int dummy; } ;
struct jz_icdc {struct regmap* regmap; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  JZ4725B_CODEC_REG_IFR ; 
 int /*<<< orphan*/  REG_IFR_RAMP_DOWN_DONE_OFFSET ; 
 int /*<<< orphan*/  REG_IFR_RAMP_UP_DONE_OFFSET ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int regmap_read_poll_timeout (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct jz_icdc* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4725b_out_stage_enable(struct snd_soc_dapm_widget *w,
				    struct snd_kcontrol *kcontrol,
				    int event)
{
	struct snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	struct jz_icdc *icdc = snd_soc_component_get_drvdata(codec);
	struct regmap *map = icdc->regmap;
	unsigned int val;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		return regmap_update_bits(map, JZ4725B_CODEC_REG_IFR,
					  BIT(REG_IFR_RAMP_UP_DONE_OFFSET), 0);
	case SND_SOC_DAPM_POST_PMU:
		return regmap_read_poll_timeout(map, JZ4725B_CODEC_REG_IFR,
			       val, val & BIT(REG_IFR_RAMP_UP_DONE_OFFSET),
			       100000, 500000);
	case SND_SOC_DAPM_PRE_PMD:
		return regmap_update_bits(map, JZ4725B_CODEC_REG_IFR,
				BIT(REG_IFR_RAMP_DOWN_DONE_OFFSET), 0);
	case SND_SOC_DAPM_POST_PMD:
		return regmap_read_poll_timeout(map, JZ4725B_CODEC_REG_IFR,
			       val, val & BIT(REG_IFR_RAMP_DOWN_DONE_OFFSET),
			       100000, 500000);
	default:
		return -EINVAL;
	}
}