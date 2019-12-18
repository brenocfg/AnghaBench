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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  boost_vtge; } ;
struct cs35l34_private {int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L34_BST_CVTL_MASK ; 
 int /*<<< orphan*/  CS35L34_BST_CVTR_V_CTL ; 
 int /*<<< orphan*/  CS35L34_MUTE ; 
 int /*<<< orphan*/  CS35L34_PROTECT_CTL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l34_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cs35l34_main_amp_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct cs35l34_private *priv = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(priv->regmap, CS35L34_BST_CVTR_V_CTL,
				CS35L34_BST_CVTL_MASK, priv->pdata.boost_vtge);
		usleep_range(5000, 5100);
		regmap_update_bits(priv->regmap, CS35L34_PROTECT_CTL,
						CS35L34_MUTE, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(priv->regmap, CS35L34_BST_CVTR_V_CTL,
			CS35L34_BST_CVTL_MASK, 0);
		regmap_update_bits(priv->regmap, CS35L34_PROTECT_CTL,
			CS35L34_MUTE, CS35L34_MUTE);
		usleep_range(5000, 5100);
		break;
	default:
		pr_err("Invalid event = 0x%x\n", event);
	}
	return 0;
}