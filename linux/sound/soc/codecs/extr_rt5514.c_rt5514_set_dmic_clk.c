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
struct TYPE_2__ {scalar_t__ dmic_init_delay; } ;
struct rt5514_priv {TYPE_1__ pdata; int /*<<< orphan*/  regmap; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5514_CLK_CTRL1 ; 
 int /*<<< orphan*/  RT5514_CLK_DMIC_OUT_SEL_MASK ; 
 int RT5514_CLK_DMIC_OUT_SEL_SFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rt5514_calc_dmic_clk (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5514_set_dmic_clk(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	int idx;

	idx = rt5514_calc_dmic_clk(component, rt5514->sysclk);
	if (idx < 0)
		dev_err(component->dev, "Failed to set DMIC clock\n");
	else
		regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL1,
			RT5514_CLK_DMIC_OUT_SEL_MASK,
			idx << RT5514_CLK_DMIC_OUT_SEL_SFT);

	if (rt5514->pdata.dmic_init_delay)
		msleep(rt5514->pdata.dmic_init_delay);

	return idx;
}