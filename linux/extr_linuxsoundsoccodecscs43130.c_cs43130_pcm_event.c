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
struct cs43130_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CS43130_CHIP_ID 134 
 int /*<<< orphan*/  CS43130_MUTE_EN ; 
 int /*<<< orphan*/  CS43130_MUTE_MASK ; 
 int /*<<< orphan*/  CS43130_PCM_PATH_CTL_1 ; 
#define  CS43131_CHIP_ID 133 
#define  CS43198_CHIP_ID 132 
#define  CS4399_CHIP_ID 131 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mute_seq ; 
 int /*<<< orphan*/  pcm_seq ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmute_seq ; 

__attribute__((used)) static int cs43130_pcm_event(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, pcm_seq,
					       ARRAY_SIZE(pcm_seq));
			break;
		}
		break;
	case SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(cs43130->regmap, CS43130_PCM_PATH_CTL_1,
				   CS43130_MUTE_MASK, 0);
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, unmute_seq,
					       ARRAY_SIZE(unmute_seq));
			break;
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, mute_seq,
					       ARRAY_SIZE(mute_seq));
			regmap_update_bits(cs43130->regmap,
					   CS43130_PCM_PATH_CTL_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			/*
			 * PCM Power Down Sequence
			 * According to Design, 130ms is preferred.
			 */
			msleep(130);
			break;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			regmap_update_bits(cs43130->regmap,
					   CS43130_PCM_PATH_CTL_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			break;
		}
		break;
	default:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		return -EINVAL;
	}
	return 0;
}