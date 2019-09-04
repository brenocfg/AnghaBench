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
struct snd_soc_dapm_context {int bias_level; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs53l30_private {int /*<<< orphan*/  mclk; int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 unsigned int CS53L30_DIGSFT_MASK ; 
 int /*<<< orphan*/  CS53L30_INT_MASK ; 
 int /*<<< orphan*/  CS53L30_IS ; 
 int /*<<< orphan*/  CS53L30_MCLKCTL ; 
 unsigned int CS53L30_MCLK_DIS ; 
 unsigned int CS53L30_MCLK_DIS_MASK ; 
 unsigned int CS53L30_PDN_DONE ; 
 unsigned int CS53L30_PDN_LP_MASK ; 
 int CS53L30_PDN_POLL_MAX ; 
 unsigned int CS53L30_PDN_ULP ; 
 unsigned int CS53L30_PDN_ULP_MASK ; 
 int /*<<< orphan*/  CS53L30_PWRCTL ; 
 int /*<<< orphan*/  CS53L30_SFT_RAMP ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs53l30_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs53l30_set_bias_level(struct snd_soc_component *component,
				  enum snd_soc_bias_level level)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct cs53l30_private *priv = snd_soc_component_get_drvdata(component);
	unsigned int reg;
	int i, inter_max_check, ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		if (dapm->bias_level == SND_SOC_BIAS_STANDBY)
			regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
					   CS53L30_PDN_LP_MASK, 0);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (dapm->bias_level == SND_SOC_BIAS_OFF) {
			ret = clk_prepare_enable(priv->mclk);
			if (ret) {
				dev_err(component->dev,
					"failed to enable MCLK: %d\n", ret);
				return ret;
			}
			regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
					   CS53L30_MCLK_DIS_MASK, 0);
			regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
					   CS53L30_PDN_ULP_MASK, 0);
			msleep(50);
		} else {
			regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
					   CS53L30_PDN_ULP_MASK,
					   CS53L30_PDN_ULP);
		}
		break;
	case SND_SOC_BIAS_OFF:
		regmap_update_bits(priv->regmap, CS53L30_INT_MASK,
				   CS53L30_PDN_DONE, 0);
		/*
		 * If digital softramp is set, the amount of time required
		 * for power down increases and depends on the digital
		 * volume setting.
		 */

		/* Set the max possible time if digsft is set */
		regmap_read(priv->regmap, CS53L30_SFT_RAMP, &reg);
		if (reg & CS53L30_DIGSFT_MASK)
			inter_max_check = CS53L30_PDN_POLL_MAX;
		else
			inter_max_check = 10;

		regmap_update_bits(priv->regmap, CS53L30_PWRCTL,
				   CS53L30_PDN_ULP_MASK,
				   CS53L30_PDN_ULP);
		/* PDN_DONE will take a min of 20ms to be set.*/
		msleep(20);
		/* Clr status */
		regmap_read(priv->regmap, CS53L30_IS, &reg);
		for (i = 0; i < inter_max_check; i++) {
			if (inter_max_check < 10) {
				usleep_range(1000, 1100);
				regmap_read(priv->regmap, CS53L30_IS, &reg);
				if (reg & CS53L30_PDN_DONE)
					break;
			} else {
				usleep_range(10000, 10100);
				regmap_read(priv->regmap, CS53L30_IS, &reg);
				if (reg & CS53L30_PDN_DONE)
					break;
			}
		}
		/* PDN_DONE is set. We now can disable the MCLK */
		regmap_update_bits(priv->regmap, CS53L30_INT_MASK,
				   CS53L30_PDN_DONE, CS53L30_PDN_DONE);
		regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
				   CS53L30_MCLK_DIS_MASK,
				   CS53L30_MCLK_DIS);
		clk_disable_unprepare(priv->mclk);
		break;
	}

	return 0;
}