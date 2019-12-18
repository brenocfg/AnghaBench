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
struct snd_soc_component {int dummy; } ;
struct regmap {int dummy; } ;
struct jz_icdc {struct regmap* regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ4725B_CODEC_REG_PMR2 ; 
 int /*<<< orphan*/  REG_PMR2_SB_OFFSET ; 
 int /*<<< orphan*/  REG_PMR2_SB_SLEEP_OFFSET ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz_icdc* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int jz4725b_codec_set_bias_level(struct snd_soc_component *component,
					enum snd_soc_bias_level level)
{
	struct jz_icdc *icdc = snd_soc_component_get_drvdata(component);
	struct regmap *map = icdc->regmap;

	switch (level) {
	case SND_SOC_BIAS_ON:
		regmap_update_bits(map, JZ4725B_CODEC_REG_PMR2,
				   BIT(REG_PMR2_SB_SLEEP_OFFSET), 0);
		break;
	case SND_SOC_BIAS_PREPARE:
		/* Enable sound hardware */
		regmap_update_bits(map, JZ4725B_CODEC_REG_PMR2,
				   BIT(REG_PMR2_SB_OFFSET), 0);
		msleep(224);
		break;
	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(map, JZ4725B_CODEC_REG_PMR2,
				   BIT(REG_PMR2_SB_SLEEP_OFFSET),
				   BIT(REG_PMR2_SB_SLEEP_OFFSET));
		break;
	case SND_SOC_BIAS_OFF:
		regmap_update_bits(map, JZ4725B_CODEC_REG_PMR2,
				   BIT(REG_PMR2_SB_OFFSET),
				   BIT(REG_PMR2_SB_OFFSET));
		break;
	}

	return 0;
}