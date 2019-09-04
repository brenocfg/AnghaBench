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
struct lm49453_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  LM49453_CHIP_EN ; 
 int /*<<< orphan*/  LM49453_P0_PMC_SETUP_REG ; 
 int /*<<< orphan*/  LM49453_PMC_SETUP_CHIP_EN ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct lm49453_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm49453_set_bias_level(struct snd_soc_component *component,
				  enum snd_soc_bias_level level)
{
	struct lm49453_priv *lm49453 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(lm49453->regmap);

		snd_soc_component_update_bits(component, LM49453_P0_PMC_SETUP_REG,
				    LM49453_PMC_SETUP_CHIP_EN, LM49453_CHIP_EN);
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, LM49453_P0_PMC_SETUP_REG,
				    LM49453_PMC_SETUP_CHIP_EN, 0);
		break;
	}

	return 0;
}