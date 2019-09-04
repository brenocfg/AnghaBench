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
struct rt5682_priv {unsigned int sysclk; int sysclk_src; scalar_t__* master; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t RT5682_AIF2 ; 
 unsigned int RT5682_CLK_SRC_MCLK ; 
 unsigned int RT5682_CLK_SRC_PLL1 ; 
 unsigned int RT5682_CLK_SRC_PLL2 ; 
 unsigned int RT5682_CLK_SRC_RCCLK ; 
 int /*<<< orphan*/  RT5682_GLB_CLK ; 
 int /*<<< orphan*/  RT5682_I2S2_SRC_MASK ; 
 unsigned int RT5682_I2S2_SRC_SFT ; 
 int /*<<< orphan*/  RT5682_I2S_M_CLK_CTRL_1 ; 
 int /*<<< orphan*/  RT5682_SCLK_SRC_MASK ; 
 unsigned int RT5682_SCLK_SRC_MCLK ; 
 unsigned int RT5682_SCLK_SRC_PLL1 ; 
 unsigned int RT5682_SCLK_SRC_PLL2 ; 
 unsigned int RT5682_SCLK_SRC_RCCLK ; 
#define  RT5682_SCLK_S_MCLK 131 
#define  RT5682_SCLK_S_PLL1 130 
#define  RT5682_SCLK_S_PLL2 129 
#define  RT5682_SCLK_S_RCCLK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rt5682_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int rt5682_set_component_sysclk(struct snd_soc_component *component,
		int clk_id, int source, unsigned int freq, int dir)
{
	struct rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0, src = 0;

	if (freq == rt5682->sysclk && clk_id == rt5682->sysclk_src)
		return 0;

	switch (clk_id) {
	case RT5682_SCLK_S_MCLK:
		reg_val |= RT5682_SCLK_SRC_MCLK;
		src = RT5682_CLK_SRC_MCLK;
		break;
	case RT5682_SCLK_S_PLL1:
		reg_val |= RT5682_SCLK_SRC_PLL1;
		src = RT5682_CLK_SRC_PLL1;
		break;
	case RT5682_SCLK_S_PLL2:
		reg_val |= RT5682_SCLK_SRC_PLL2;
		src = RT5682_CLK_SRC_PLL2;
		break;
	case RT5682_SCLK_S_RCCLK:
		reg_val |= RT5682_SCLK_SRC_RCCLK;
		src = RT5682_CLK_SRC_RCCLK;
		break;
	default:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, RT5682_GLB_CLK,
		RT5682_SCLK_SRC_MASK, reg_val);

	if (rt5682->master[RT5682_AIF2]) {
		snd_soc_component_update_bits(component,
			RT5682_I2S_M_CLK_CTRL_1, RT5682_I2S2_SRC_MASK,
			src << RT5682_I2S2_SRC_SFT);
	}

	rt5682->sysclk = freq;
	rt5682->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	return 0;
}