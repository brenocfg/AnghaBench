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
struct aic3x_priv {int /*<<< orphan*/  power; int /*<<< orphan*/  master; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  AIC3X_PLL_PROGA_REG ; 
 int /*<<< orphan*/  PLL_ENABLE ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  aic3x_set_power (struct snd_soc_component*,int) ; 
 int const snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic3x_set_bias_level(struct snd_soc_component *component,
				enum snd_soc_bias_level level)
{
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY &&
		    aic3x->master) {
			/* enable pll */
			snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG,
					    PLL_ENABLE, PLL_ENABLE);
		}
		break;
	case SND_SOC_BIAS_STANDBY:
		if (!aic3x->power)
			aic3x_set_power(component, 1);
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE &&
		    aic3x->master) {
			/* disable pll */
			snd_soc_component_update_bits(component, AIC3X_PLL_PROGA_REG,
					    PLL_ENABLE, 0);
		}
		break;
	case SND_SOC_BIAS_OFF:
		if (aic3x->power)
			aic3x_set_power(component, 0);
		break;
	}

	return 0;
}