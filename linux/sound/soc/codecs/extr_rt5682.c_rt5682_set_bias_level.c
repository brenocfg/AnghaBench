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
struct rt5682_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int RT5682_DIG_GATE_CTRL ; 
 int /*<<< orphan*/  RT5682_PWR_ANLG_1 ; 
 int RT5682_PWR_BG ; 
 int /*<<< orphan*/  RT5682_PWR_DIG_1 ; 
 int RT5682_PWR_LDO ; 
#define  SND_SOC_BIAS_OFF 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct rt5682_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5682_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
			RT5682_PWR_BG, RT5682_PWR_BG);
		regmap_update_bits(rt5682->regmap, RT5682_PWR_DIG_1,
			RT5682_DIG_GATE_CTRL | RT5682_PWR_LDO,
			RT5682_DIG_GATE_CTRL | RT5682_PWR_LDO);
		break;

	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(rt5682->regmap, RT5682_PWR_DIG_1,
			RT5682_DIG_GATE_CTRL, RT5682_DIG_GATE_CTRL);
		break;
	case SND_SOC_BIAS_OFF:
		regmap_update_bits(rt5682->regmap, RT5682_PWR_DIG_1,
			RT5682_DIG_GATE_CTRL | RT5682_PWR_LDO, 0);
		regmap_update_bits(rt5682->regmap, RT5682_PWR_ANLG_1,
			RT5682_PWR_BG, 0);
		break;

	default:
		break;
	}

	return 0;
}