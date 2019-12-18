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
struct adav80x {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ADAV80X_DAC_CTRL1 ; 
 unsigned int ADAV80X_DAC_CTRL1_PD ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adav80x_set_bias_level(struct snd_soc_component *component,
		enum snd_soc_bias_level level)
{
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);
	unsigned int mask = ADAV80X_DAC_CTRL1_PD;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL1, mask,
			0x00);
		break;
	case SND_SOC_BIAS_OFF:
		regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL1, mask,
			mask);
		break;
	}

	return 0;
}