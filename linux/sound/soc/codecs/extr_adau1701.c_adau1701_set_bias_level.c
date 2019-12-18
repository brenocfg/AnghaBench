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
struct adau1701 {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_AUXNPOW ; 
 unsigned int ADAU1701_AUXNPOW_VBPD ; 
 unsigned int ADAU1701_AUXNPOW_VRPD ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1701_set_bias_level(struct snd_soc_component *component,
		enum snd_soc_bias_level level)
{
	unsigned int mask = ADAU1701_AUXNPOW_VBPD | ADAU1701_AUXNPOW_VRPD;
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* Enable VREF and VREF buffer */
		regmap_update_bits(adau1701->regmap,
				   ADAU1701_AUXNPOW, mask, 0x00);
		break;
	case SND_SOC_BIAS_OFF:
		/* Disable VREF and VREF buffer */
		regmap_update_bits(adau1701->regmap,
				   ADAU1701_AUXNPOW, mask, mask);
		break;
	}

	return 0;
}