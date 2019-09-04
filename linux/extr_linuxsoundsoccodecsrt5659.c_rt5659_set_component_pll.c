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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5659_priv {int pll_src; unsigned int pll_in; unsigned int pll_out; } ;
struct rl6231_pll_code {int m_bp; int m_code; int n_code; int k_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5659_GLB_CLK ; 
 int /*<<< orphan*/  RT5659_PLL1_SRC_BCLK1 ; 
 int /*<<< orphan*/  RT5659_PLL1_SRC_BCLK2 ; 
 int /*<<< orphan*/  RT5659_PLL1_SRC_BCLK3 ; 
 int /*<<< orphan*/  RT5659_PLL1_SRC_MASK ; 
 int /*<<< orphan*/  RT5659_PLL1_SRC_MCLK ; 
#define  RT5659_PLL1_S_BCLK1 131 
#define  RT5659_PLL1_S_BCLK2 130 
#define  RT5659_PLL1_S_BCLK3 129 
#define  RT5659_PLL1_S_MCLK 128 
 int /*<<< orphan*/  RT5659_PLL_CTRL_1 ; 
 int /*<<< orphan*/  RT5659_PLL_CTRL_2 ; 
 int RT5659_PLL_M_BP_SFT ; 
 int RT5659_PLL_M_SFT ; 
 int RT5659_PLL_N_SFT ; 
 int /*<<< orphan*/  RT5659_SCLK_SRC_MASK ; 
 int /*<<< orphan*/  RT5659_SCLK_SRC_MCLK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int rl6231_pll_calc (unsigned int,unsigned int,struct rl6231_pll_code*) ; 
 struct rt5659_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt5659_set_component_pll(struct snd_soc_component *component, int pll_id,
				int source, unsigned int freq_in,
				unsigned int freq_out)
{
	struct rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	struct rl6231_pll_code pll_code;
	int ret;

	if (source == rt5659->pll_src && freq_in == rt5659->pll_in &&
	    freq_out == rt5659->pll_out)
		return 0;

	if (!freq_in || !freq_out) {
		dev_dbg(component->dev, "PLL disabled\n");

		rt5659->pll_in = 0;
		rt5659->pll_out = 0;
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
			RT5659_SCLK_SRC_MASK, RT5659_SCLK_SRC_MCLK);
		return 0;
	}

	switch (source) {
	case RT5659_PLL1_S_MCLK:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
			RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_MCLK);
		break;
	case RT5659_PLL1_S_BCLK1:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
				RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_BCLK1);
		break;
	case RT5659_PLL1_S_BCLK2:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
				RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_BCLK2);
		break;
	case RT5659_PLL1_S_BCLK3:
		snd_soc_component_update_bits(component, RT5659_GLB_CLK,
				RT5659_PLL1_SRC_MASK, RT5659_PLL1_SRC_BCLK3);
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

	snd_soc_component_write(component, RT5659_PLL_CTRL_1,
		pll_code.n_code << RT5659_PLL_N_SFT | pll_code.k_code);
	snd_soc_component_write(component, RT5659_PLL_CTRL_2,
		(pll_code.m_bp ? 0 : pll_code.m_code) << RT5659_PLL_M_SFT |
		pll_code.m_bp << RT5659_PLL_M_BP_SFT);

	rt5659->pll_in = freq_in;
	rt5659->pll_out = freq_out;
	rt5659->pll_src = source;

	return 0;
}