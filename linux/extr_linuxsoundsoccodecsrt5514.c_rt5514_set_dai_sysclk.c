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
struct rt5514_priv {unsigned int sysclk; int sysclk_src; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5514_CLK_CTRL2 ; 
 int /*<<< orphan*/  RT5514_CLK_SYS_PRE_SEL_MASK ; 
 unsigned int RT5514_CLK_SYS_PRE_SEL_MCLK ; 
 unsigned int RT5514_CLK_SYS_PRE_SEL_PLL ; 
#define  RT5514_SCLK_S_MCLK 129 
#define  RT5514_SCLK_S_PLL1 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5514_set_dai_sysclk(struct snd_soc_dai *dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;

	if (freq == rt5514->sysclk && clk_id == rt5514->sysclk_src)
		return 0;

	switch (clk_id) {
	case RT5514_SCLK_S_MCLK:
		reg_val |= RT5514_CLK_SYS_PRE_SEL_MCLK;
		break;

	case RT5514_SCLK_S_PLL1:
		reg_val |= RT5514_CLK_SYS_PRE_SEL_PLL;
		break;

	default:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}

	regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL2,
		RT5514_CLK_SYS_PRE_SEL_MASK, reg_val);

	rt5514->sysclk = freq;
	rt5514->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	return 0;
}