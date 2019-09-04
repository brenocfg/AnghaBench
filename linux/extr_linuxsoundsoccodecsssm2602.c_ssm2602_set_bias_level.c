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
struct ssm2602_priv {int clk_out_pwr; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int PWR_CLK_OUT_PDN ; 
 int PWR_OSC_PDN ; 
 int PWR_POWER_OFF ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  SSM2602_PWR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct ssm2602_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ssm2602_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* vref/mid on, osc and clkout on if enabled */
		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_POWER_OFF | PWR_CLK_OUT_PDN | PWR_OSC_PDN,
			ssm2602->clk_out_pwr);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_POWER_OFF | PWR_CLK_OUT_PDN | PWR_OSC_PDN,
			PWR_CLK_OUT_PDN | PWR_OSC_PDN);
		break;
	case SND_SOC_BIAS_OFF:
		/* everything off */
		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_POWER_OFF, PWR_POWER_OFF);
		break;

	}
	return 0;
}