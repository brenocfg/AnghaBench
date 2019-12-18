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
struct cs35l33_private {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L33_CLK_CTL ; 
 int /*<<< orphan*/  CS35L33_INT_STATUS_2 ; 
 int /*<<< orphan*/  CS35L33_MCLKDIS ; 
 int /*<<< orphan*/  CS35L33_PDN_ALL ; 
 unsigned int CS35L33_PDN_DONE ; 
 int /*<<< orphan*/  CS35L33_PWRCTL1 ; 
 int EINVAL ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs35l33_set_bias_level(struct snd_soc_component *component,
				  enum snd_soc_bias_level level)
{
	unsigned int val;
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_ALL, 0);
		regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
				    CS35L33_MCLKDIS, 0);
		break;
	case SND_SOC_BIAS_STANDBY:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_ALL, CS35L33_PDN_ALL);
		regmap_read(priv->regmap, CS35L33_INT_STATUS_2, &val);
		usleep_range(1000, 1100);
		if (val & CS35L33_PDN_DONE)
			regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
					    CS35L33_MCLKDIS, CS35L33_MCLKDIS);
		break;
	case SND_SOC_BIAS_OFF:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}