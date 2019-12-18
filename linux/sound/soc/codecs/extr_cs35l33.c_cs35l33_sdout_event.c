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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct cs35l33_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  is_tdm_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L33_CLK_CTL ; 
 unsigned int CS35L33_PDN_TDM ; 
 int /*<<< orphan*/  CS35L33_PWRCTL2 ; 
 unsigned int CS35L33_SDOUT_3ST_I2S ; 
 unsigned int CS35L33_SDOUT_3ST_TDM ; 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l33_sdout_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);
	unsigned int mask = CS35L33_SDOUT_3ST_I2S | CS35L33_PDN_TDM;
	unsigned int mask2 = CS35L33_SDOUT_3ST_TDM;
	unsigned int val, val2;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (priv->is_tdm_mode) {
			/* set sdout_3st_i2s and reset pdn_tdm */
			val = CS35L33_SDOUT_3ST_I2S;
			/* reset sdout_3st_tdm */
			val2 = 0;
		} else {
			/* reset sdout_3st_i2s and set pdn_tdm */
			val = CS35L33_PDN_TDM;
			/* set sdout_3st_tdm */
			val2 = CS35L33_SDOUT_3ST_TDM;
		}
		dev_dbg(component->dev, "SDOUT turned on\n");
		break;
	case SND_SOC_DAPM_PRE_PMD:
		val = CS35L33_SDOUT_3ST_I2S | CS35L33_PDN_TDM;
		val2 = CS35L33_SDOUT_3ST_TDM;
		dev_dbg(component->dev, "SDOUT turned off\n");
		break;
	default:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		return 0;
	}

	regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
		mask, val);
	regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
		mask2, val2);

	return 0;
}