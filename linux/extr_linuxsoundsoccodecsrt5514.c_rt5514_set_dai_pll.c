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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5514_priv {unsigned int pll_in; unsigned int pll_out; int pll_src; int /*<<< orphan*/  regmap; } ;
struct rl6231_pll_code {int m_bp; int m_code; int n_code; int k_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5514_ANA_CTRL_PLL1_1 ; 
 int /*<<< orphan*/  RT5514_ANA_CTRL_PLL1_2 ; 
 int /*<<< orphan*/  RT5514_CLK_CTRL2 ; 
 int /*<<< orphan*/  RT5514_CLK_SYS_PRE_SEL_MASK ; 
 int RT5514_CLK_SYS_PRE_SEL_MCLK ; 
#define  RT5514_PLL1_S_BCLK 129 
#define  RT5514_PLL1_S_MCLK 128 
 int /*<<< orphan*/  RT5514_PLL_1_SEL_MASK ; 
 int RT5514_PLL_1_SEL_MCLK ; 
 int RT5514_PLL_1_SEL_SCLK ; 
 int RT5514_PLL_K_SFT ; 
 int /*<<< orphan*/  RT5514_PLL_M_BP ; 
 int RT5514_PLL_M_BP_SFT ; 
 int RT5514_PLL_M_SFT ; 
 int RT5514_PLL_N_SFT ; 
 int /*<<< orphan*/  RT5514_PLL_SOURCE_CTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rl6231_pll_calc (unsigned int,unsigned int,struct rl6231_pll_code*) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5514_set_dai_pll(struct snd_soc_dai *dai, int pll_id, int source,
			unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_component *component = dai->component;
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	struct rl6231_pll_code pll_code;
	int ret;

	if (!freq_in || !freq_out) {
		dev_dbg(component->dev, "PLL disabled\n");

		rt5514->pll_in = 0;
		rt5514->pll_out = 0;
		regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL2,
			RT5514_CLK_SYS_PRE_SEL_MASK,
			RT5514_CLK_SYS_PRE_SEL_MCLK);

		return 0;
	}

	if (source == rt5514->pll_src && freq_in == rt5514->pll_in &&
	    freq_out == rt5514->pll_out)
		return 0;

	switch (source) {
	case RT5514_PLL1_S_MCLK:
		regmap_update_bits(rt5514->regmap, RT5514_PLL_SOURCE_CTRL,
			RT5514_PLL_1_SEL_MASK, RT5514_PLL_1_SEL_MCLK);
		break;

	case RT5514_PLL1_S_BCLK:
		regmap_update_bits(rt5514->regmap, RT5514_PLL_SOURCE_CTRL,
			RT5514_PLL_1_SEL_MASK, RT5514_PLL_1_SEL_SCLK);
		break;

	default:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		return -EINVAL;
	}

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	if (ret < 0) {
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		return ret;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	regmap_write(rt5514->regmap, RT5514_ANA_CTRL_PLL1_1,
		pll_code.k_code << RT5514_PLL_K_SFT |
		pll_code.n_code << RT5514_PLL_N_SFT |
		(pll_code.m_bp ? 0 : pll_code.m_code) << RT5514_PLL_M_SFT);
	regmap_update_bits(rt5514->regmap, RT5514_ANA_CTRL_PLL1_2,
		RT5514_PLL_M_BP, pll_code.m_bp << RT5514_PLL_M_BP_SFT);

	rt5514->pll_in = freq_in;
	rt5514->pll_out = freq_out;
	rt5514->pll_src = source;

	return 0;
}