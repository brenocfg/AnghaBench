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
typedef  int u8 ;
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs43130_private {int clk_req; int /*<<< orphan*/  regmap; TYPE_1__* dais; int /*<<< orphan*/  clk_mutex; scalar_t__ pll_bypass; int /*<<< orphan*/  mclk; } ;
struct TYPE_2__ {scalar_t__ dai_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS43130_DSD_INT_CFG ; 
 int CS43130_DSD_MASTER ; 
 int /*<<< orphan*/  CS43130_DSD_PATH_CTL_2 ; 
 int CS43130_DSD_SPEED_MASK ; 
 int CS43130_DSD_SPEED_SHIFT ; 
 int CS43130_DSD_SRC_DSD ; 
 int CS43130_DSD_SRC_MASK ; 
 int CS43130_DSD_SRC_SHIFT ; 
 int CS43130_MCLK_22M ; 
 unsigned int CS43130_MCLK_24M ; 
 int /*<<< orphan*/  CS43130_MCLK_SRC_EXT ; 
 int /*<<< orphan*/  CS43130_MCLK_SRC_PLL ; 
 int EINVAL ; 
 scalar_t__ SND_SOC_DAIFMT_CBM_CFM ; 
 int /*<<< orphan*/  cs43130_change_clksrc (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs43130_pcm_dsd_mix (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs43130_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs43130_dsd_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);
	unsigned int required_clk;
	u8 dsd_speed;

	mutex_lock(&cs43130->clk_mutex);
	if (!cs43130->clk_req) {
		/* no DAI is currently using clk */
		if (!(CS43130_MCLK_22M % params_rate(params)))
			required_clk = CS43130_MCLK_22M;
		else
			required_clk = CS43130_MCLK_24M;

		cs43130_set_pll(component, 0, 0, cs43130->mclk, required_clk);
		if (cs43130->pll_bypass)
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_EXT);
		else
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_PLL);
	}

	cs43130->clk_req++;
	if (cs43130->clk_req == 2)
		cs43130_pcm_dsd_mix(true, cs43130->regmap);
	mutex_unlock(&cs43130->clk_mutex);

	switch (params_rate(params)) {
	case 176400:
		dsd_speed = 0;
		break;
	case 352800:
		dsd_speed = 1;
		break;
	default:
		dev_err(component->dev, "Rate(%u) not supported\n",
			params_rate(params));
		return -EINVAL;
	}

	if (cs43130->dais[dai->id].dai_mode == SND_SOC_DAIFMT_CBM_CFM)
		regmap_update_bits(cs43130->regmap, CS43130_DSD_INT_CFG,
				   CS43130_DSD_MASTER, CS43130_DSD_MASTER);
	else
		regmap_update_bits(cs43130->regmap, CS43130_DSD_INT_CFG,
				   CS43130_DSD_MASTER, 0);

	regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
			   CS43130_DSD_SPEED_MASK,
			   dsd_speed << CS43130_DSD_SPEED_SHIFT);
	regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
			   CS43130_DSD_SRC_MASK, CS43130_DSD_SRC_DSD <<
			   CS43130_DSD_SRC_SHIFT);

	return 0;
}