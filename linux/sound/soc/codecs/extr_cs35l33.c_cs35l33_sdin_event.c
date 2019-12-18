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
struct cs35l33_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  amp_cal; int /*<<< orphan*/  is_tdm_mode; } ;

/* Variables and functions */
 unsigned int CS35L33_AMP_CAL ; 
 int /*<<< orphan*/  CS35L33_CLASSD_CTL ; 
 unsigned int CS35L33_PDN_BST ; 
 unsigned int CS35L33_PDN_TDM ; 
 int /*<<< orphan*/  CS35L33_PWRCTL1 ; 
 int /*<<< orphan*/  CS35L33_PWRCTL2 ; 
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs35l33_sdin_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);
	unsigned int val;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_BST, 0);
		val = priv->is_tdm_mode ? 0 : CS35L33_PDN_TDM;
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
				    CS35L33_PDN_TDM, val);
		dev_dbg(component->dev, "BST turned on\n");
		break;
	case SND_SOC_DAPM_POST_PMU:
		dev_dbg(component->dev, "SDIN turned on\n");
		if (!priv->amp_cal) {
			regmap_update_bits(priv->regmap, CS35L33_CLASSD_CTL,
				    CS35L33_AMP_CAL, CS35L33_AMP_CAL);
			dev_dbg(component->dev, "Amp calibration started\n");
			usleep_range(10000, 11000);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
				    CS35L33_PDN_TDM, CS35L33_PDN_TDM);
		usleep_range(4000, 4100);
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_BST, CS35L33_PDN_BST);
		dev_dbg(component->dev, "BST and SDIN turned off\n");
		break;
	default:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);

	}

	return 0;
}