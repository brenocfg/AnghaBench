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
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5640_priv {unsigned int sysclk; int sysclk_src; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5640_GLB_CLK ; 
 int /*<<< orphan*/  RT5640_PWR_ANLG2 ; 
 unsigned int RT5640_PWR_PLL ; 
 unsigned int RT5640_SCLK_SRC_MASK ; 
 unsigned int RT5640_SCLK_SRC_MCLK ; 
 unsigned int RT5640_SCLK_SRC_PLL1 ; 
 unsigned int RT5640_SCLK_SRC_RCCLK ; 
#define  RT5640_SCLK_S_MCLK 130 
#define  RT5640_SCLK_S_PLL1 129 
#define  RT5640_SCLK_S_RCCLK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int rt5640_set_dai_sysclk(struct snd_soc_dai *dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;
	unsigned int pll_bit = 0;

	if (freq == rt5640->sysclk && clk_id == rt5640->sysclk_src)
		return 0;

	switch (clk_id) {
	case RT5640_SCLK_S_MCLK:
		reg_val |= RT5640_SCLK_SRC_MCLK;
		break;
	case RT5640_SCLK_S_PLL1:
		reg_val |= RT5640_SCLK_SRC_PLL1;
		pll_bit |= RT5640_PWR_PLL;
		break;
	case RT5640_SCLK_S_RCCLK:
		reg_val |= RT5640_SCLK_SRC_RCCLK;
		break;
	default:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, RT5640_PWR_ANLG2,
		RT5640_PWR_PLL, pll_bit);
	snd_soc_component_update_bits(component, RT5640_GLB_CLK,
		RT5640_SCLK_SRC_MASK, reg_val);
	rt5640->sysclk = freq;
	rt5640->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);
	return 0;
}