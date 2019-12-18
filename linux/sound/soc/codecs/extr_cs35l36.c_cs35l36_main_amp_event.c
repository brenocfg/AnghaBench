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
typedef  int u32 ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct cs35l36_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L36_AMP_MUTE_MASK ; 
 int CS35L36_AMP_MUTE_SHIFT ; 
 int /*<<< orphan*/  CS35L36_AMP_OUT_MUTE ; 
 int /*<<< orphan*/  CS35L36_ASP_RX1_SEL ; 
 int /*<<< orphan*/  CS35L36_GLOBAL_EN_MASK ; 
 int CS35L36_GLOBAL_EN_SHIFT ; 
 int /*<<< orphan*/  CS35L36_INT4_RAW_STATUS ; 
 int /*<<< orphan*/  CS35L36_PCM_RX_SEL_MASK ; 
 int CS35L36_PCM_RX_SEL_PCM ; 
 int CS35L36_PCM_RX_SEL_ZERO ; 
 int CS35L36_PLL_UNLOCK_MASK ; 
 int /*<<< orphan*/  CS35L36_PWR_CTRL1 ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs35l36_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs35l36_main_amp_event(struct snd_soc_dapm_widget *w,
				  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	struct cs35l36_private *cs35l36 =
			snd_soc_component_get_drvdata(component);
	u32 reg;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL1,
				   CS35L36_GLOBAL_EN_MASK,
				   1 << CS35L36_GLOBAL_EN_SHIFT);

		usleep_range(2000, 2100);

		regmap_read(cs35l36->regmap, CS35L36_INT4_RAW_STATUS, &reg);

		if (WARN_ON_ONCE(reg & CS35L36_PLL_UNLOCK_MASK))
			dev_crit(cs35l36->dev, "PLL Unlocked\n");

		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RX1_SEL,
				   CS35L36_PCM_RX_SEL_MASK,
				   CS35L36_PCM_RX_SEL_PCM);
		regmap_update_bits(cs35l36->regmap, CS35L36_AMP_OUT_MUTE,
				   CS35L36_AMP_MUTE_MASK,
				   0 << CS35L36_AMP_MUTE_SHIFT);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RX1_SEL,
				   CS35L36_PCM_RX_SEL_MASK,
				   CS35L36_PCM_RX_SEL_ZERO);
		regmap_update_bits(cs35l36->regmap, CS35L36_AMP_OUT_MUTE,
				   CS35L36_AMP_MUTE_MASK,
				   1 << CS35L36_AMP_MUTE_SHIFT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL1,
				   CS35L36_GLOBAL_EN_MASK,
				   0 << CS35L36_GLOBAL_EN_SHIFT);

		usleep_range(2000, 2100);
		break;
	default:
		dev_dbg(component->dev, "Invalid event = 0x%x\n", event);
		return -EINVAL;
	}

	return 0;
}