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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct rt5682_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RT5682_DMIC_CLK_MASK ; 
 int RT5682_DMIC_CLK_SFT ; 
 int /*<<< orphan*/  RT5682_DMIC_CTRL_1 ; 
 int rt5682_div_sel (struct rt5682_priv*,int,int const*,int /*<<< orphan*/ ) ; 
 struct rt5682_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_dmic_clk(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	struct rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	int idx = -EINVAL;
	static const int div[] = {2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128};

	idx = rt5682_div_sel(rt5682, 1500000, div, ARRAY_SIZE(div));

	snd_soc_component_update_bits(component, RT5682_DMIC_CTRL_1,
		RT5682_DMIC_CLK_MASK, idx << RT5682_DMIC_CLK_SFT);

	return 0;
}