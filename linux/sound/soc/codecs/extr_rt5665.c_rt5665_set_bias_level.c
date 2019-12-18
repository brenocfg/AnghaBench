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
struct rt5665_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  RT5665_DIG_GATE_CTRL ; 
 int /*<<< orphan*/  RT5665_DIG_MISC ; 
 int /*<<< orphan*/  RT5665_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5665_PWR_DIG_1 ; 
 int /*<<< orphan*/  RT5665_PWR_LDO ; 
 int /*<<< orphan*/  RT5665_PWR_MB ; 
#define  SND_SOC_BIAS_OFF 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt5665_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5665_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		regmap_update_bits(rt5665->regmap, RT5665_DIG_MISC,
			RT5665_DIG_GATE_CTRL, RT5665_DIG_GATE_CTRL);
		break;

	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(rt5665->regmap, RT5665_PWR_DIG_1,
			RT5665_PWR_LDO,	RT5665_PWR_LDO);
		regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_1,
			RT5665_PWR_MB, RT5665_PWR_MB);
		regmap_update_bits(rt5665->regmap, RT5665_DIG_MISC,
			RT5665_DIG_GATE_CTRL, 0);
		break;
	case SND_SOC_BIAS_OFF:
		regmap_update_bits(rt5665->regmap, RT5665_PWR_DIG_1,
			RT5665_PWR_LDO, 0);
		regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_1,
			RT5665_PWR_MB, 0);
		break;

	default:
		break;
	}

	return 0;
}