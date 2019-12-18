#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  extern_boost; } ;
struct cs35l36_private {int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 int CS35L36_BST_DIS_VP ; 
 int CS35L36_BST_EN ; 
 int /*<<< orphan*/  CS35L36_BST_EN_MASK ; 
 int CS35L36_BST_EN_SHIFT ; 
 int /*<<< orphan*/  CS35L36_PWR_CTRL2 ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs35l36_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l36_boost_event(struct snd_soc_dapm_widget *w,
			       struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	struct cs35l36_private *cs35l36 =
			snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (!cs35l36->pdata.extern_boost)
			regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL2,
					   CS35L36_BST_EN_MASK,
					   CS35L36_BST_EN <<
					   CS35L36_BST_EN_SHIFT);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (!cs35l36->pdata.extern_boost)
			regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL2,
					   CS35L36_BST_EN_MASK,
					   CS35L36_BST_DIS_VP <<
					   CS35L36_BST_EN_SHIFT);
		break;
	default:
		dev_dbg(component->dev, "Invalid event = 0x%x\n", event);
		return -EINVAL;
	}

	return 0;
}