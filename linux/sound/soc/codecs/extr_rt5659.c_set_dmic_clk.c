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
struct rt5659_priv {int sysclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5659_ADDA_CLK_1 ; 
 int /*<<< orphan*/  RT5659_DMIC_CLK_MASK ; 
 int RT5659_DMIC_CLK_SFT ; 
 int /*<<< orphan*/  RT5659_DMIC_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_I2S_PD1_SFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int rl6231_calc_dmic_clk (int) ; 
 int rl6231_get_pre_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt5659_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_dmic_clk(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	int pd, idx = -EINVAL;

	pd = rl6231_get_pre_div(rt5659->regmap,
		RT5659_ADDA_CLK_1, RT5659_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rt5659->sysclk / pd);

	if (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	else {
		snd_soc_component_update_bits(component, RT5659_DMIC_CTRL_1,
			RT5659_DMIC_CLK_MASK, idx << RT5659_DMIC_CLK_SFT);
	}
	return idx;
}