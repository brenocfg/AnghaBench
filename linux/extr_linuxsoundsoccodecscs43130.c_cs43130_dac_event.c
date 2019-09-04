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
 int /*<<< orphan*/  CS43130_DXD1 ; 
 int /*<<< orphan*/  CS43130_DXD12 ; 
 int /*<<< orphan*/  CS43130_DXD13 ; 
#define  CS43131_CHIP_ID 133 
#define  CS43198_CHIP_ID 132 
#define  CS4399_CHIP_ID 131 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dac_postpmd_seq ; 
 int /*<<< orphan*/  dac_postpmu_seq ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pop_free_seq ; 
 int /*<<< orphan*/  pop_free_seq2 ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs43130_dac_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, pop_free_seq,
					       ARRAY_SIZE(pop_free_seq));
			break;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, pop_free_seq2,
					       ARRAY_SIZE(pop_free_seq2));
			break;
		}
		break;
	case SND_SOC_DAPM_POST_PMU:
		usleep_range(10000, 10050);

		regmap_write(cs43130->regmap, CS43130_DXD1, 0x99);

		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, dac_postpmu_seq,
					       ARRAY_SIZE(dac_postpmu_seq));
			/*
			 * Per datasheet, Sec. PCM Power-Up Sequence.
			 * According to Design, CS43130_DXD12 must be 0 to meet
			 * THDN and Dynamic Range spec.
			 */
			msleep(1000);
			regmap_write(cs43130->regmap, CS43130_DXD12, 0);
			break;
		case CS43131_CHIP_ID:
		case CS43198_CHIP_ID:
			usleep_range(12000, 12010);
			regmap_write(cs43130->regmap, CS43130_DXD13, 0);
			break;
		}

		regmap_write(cs43130->regmap, CS43130_DXD1, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		switch (cs43130->dev_id) {
		case CS43130_CHIP_ID:
		case CS4399_CHIP_ID:
			regmap_multi_reg_write(cs43130->regmap, dac_postpmd_seq,
					       ARRAY_SIZE(dac_postpmd_seq));
			break;
		}
		break;
	default:
		dev_err(component->dev, "Invalid DAC event = 0x%x\n", event);
		return -EINVAL;
	}
	return 0;
}