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
struct snd_soc_dai {int /*<<< orphan*/  id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5677_priv {int pll_src; unsigned int pll_in; unsigned int pll_out; int /*<<< orphan*/  regmap; } ;
struct rl6231_pll_code {int m_bp; int m_code; int n_code; int k_code; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RT5677_AIF1 136 
#define  RT5677_AIF2 135 
#define  RT5677_AIF3 134 
#define  RT5677_AIF4 133 
 int /*<<< orphan*/  RT5677_GLB_CLK1 ; 
 int /*<<< orphan*/  RT5677_PLL1_CTRL1 ; 
 int /*<<< orphan*/  RT5677_PLL1_CTRL2 ; 
 int /*<<< orphan*/  RT5677_PLL1_SRC_BCLK1 ; 
 int /*<<< orphan*/  RT5677_PLL1_SRC_BCLK2 ; 
 int /*<<< orphan*/  RT5677_PLL1_SRC_BCLK3 ; 
 int /*<<< orphan*/  RT5677_PLL1_SRC_BCLK4 ; 
 int /*<<< orphan*/  RT5677_PLL1_SRC_MASK ; 
 int /*<<< orphan*/  RT5677_PLL1_SRC_MCLK ; 
#define  RT5677_PLL1_S_BCLK1 132 
#define  RT5677_PLL1_S_BCLK2 131 
#define  RT5677_PLL1_S_BCLK3 130 
#define  RT5677_PLL1_S_BCLK4 129 
#define  RT5677_PLL1_S_MCLK 128 
 int RT5677_PLL_M_BP_SFT ; 
 int RT5677_PLL_M_SFT ; 
 int RT5677_PLL_N_SFT ; 
 int /*<<< orphan*/  RT5677_SCLK_SRC_MASK ; 
 int /*<<< orphan*/  RT5677_SCLK_SRC_MCLK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rt5677_pll_calc (unsigned int,unsigned int,struct rl6231_pll_code*) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5677_set_dai_pll(struct snd_soc_dai *dai, int pll_id, int source,
			unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_component *component = dai->component;
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	struct rl6231_pll_code pll_code;
	int ret;

	if (source == rt5677->pll_src && freq_in == rt5677->pll_in &&
	    freq_out == rt5677->pll_out)
		return 0;

	if (!freq_in || !freq_out) {
		dev_dbg(component->dev, "PLL disabled\n");

		rt5677->pll_in = 0;
		rt5677->pll_out = 0;
		regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
			RT5677_SCLK_SRC_MASK, RT5677_SCLK_SRC_MCLK);
		return 0;
	}

	switch (source) {
	case RT5677_PLL1_S_MCLK:
		regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
			RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_MCLK);
		break;
	case RT5677_PLL1_S_BCLK1:
	case RT5677_PLL1_S_BCLK2:
	case RT5677_PLL1_S_BCLK3:
	case RT5677_PLL1_S_BCLK4:
		switch (dai->id) {
		case RT5677_AIF1:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK1);
			break;
		case RT5677_AIF2:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK2);
			break;
		case RT5677_AIF3:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK3);
			break;
		case RT5677_AIF4:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_PLL1_SRC_MASK, RT5677_PLL1_SRC_BCLK4);
			break;
		default:
			break;
		}
		break;
	default:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		return -EINVAL;
	}

	ret = rt5677_pll_calc(freq_in, freq_out, &pll_code);
	if (ret < 0) {
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		return ret;
	}

	dev_dbg(component->dev, "m_bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	regmap_write(rt5677->regmap, RT5677_PLL1_CTRL1,
		pll_code.n_code << RT5677_PLL_N_SFT | pll_code.k_code);
	regmap_write(rt5677->regmap, RT5677_PLL1_CTRL2,
		(pll_code.m_bp ? 0 : pll_code.m_code) << RT5677_PLL_M_SFT |
		pll_code.m_bp << RT5677_PLL_M_BP_SFT);

	rt5677->pll_in = freq_in;
	rt5677->pll_out = freq_out;
	rt5677->pll_src = source;

	return 0;
}