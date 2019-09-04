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
struct adau {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1781_DIG_PWDN1 ; 
 int /*<<< orphan*/  ADAU17X1_CLOCK_CONTROL ; 
 int ADAU17X1_CLOCK_CONTROL_SYSCLK_EN ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1781_set_bias_level(struct snd_soc_component *component,
		enum snd_soc_bias_level level)
{
	struct adau *adau = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN);

		/* Precharge */
		regmap_update_bits(adau->regmap, ADAU1781_DIG_PWDN1, 0x8, 0x8);
		break;
	case SND_SOC_BIAS_OFF:
		regmap_update_bits(adau->regmap, ADAU1781_DIG_PWDN1, 0xc, 0x0);
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_SYSCLK_EN, 0);
		break;
	}

	return 0;
}