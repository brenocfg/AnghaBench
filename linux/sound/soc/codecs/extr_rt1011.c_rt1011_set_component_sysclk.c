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
struct rt1011_priv {unsigned int sysclk; int sysclk_src; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT1011_CLK_2 ; 
 int /*<<< orphan*/  RT1011_CLK_DET ; 
 unsigned int RT1011_EN_MCLK_DET ; 
 int /*<<< orphan*/  RT1011_EN_MCLK_DET_MASK ; 
 unsigned int RT1011_FS_SYS_PRE_BCLK ; 
 int /*<<< orphan*/  RT1011_FS_SYS_PRE_MASK ; 
 unsigned int RT1011_FS_SYS_PRE_MCLK ; 
 unsigned int RT1011_FS_SYS_PRE_PLL1 ; 
 unsigned int RT1011_FS_SYS_PRE_RCCLK ; 
#define  RT1011_FS_SYS_PRE_S_BCLK 131 
#define  RT1011_FS_SYS_PRE_S_MCLK 130 
#define  RT1011_FS_SYS_PRE_S_PLL1 129 
#define  RT1011_FS_SYS_PRE_S_RCCLK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rt1011_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int rt1011_set_component_sysclk(struct snd_soc_component *component,
		int clk_id, int source, unsigned int freq, int dir)
{
	struct rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;

	if (freq == rt1011->sysclk && clk_id == rt1011->sysclk_src)
		return 0;

	/* disable MCLK detect in default */
	snd_soc_component_update_bits(component, RT1011_CLK_DET,
			RT1011_EN_MCLK_DET_MASK, 0);

	switch (clk_id) {
	case RT1011_FS_SYS_PRE_S_MCLK:
		reg_val |= RT1011_FS_SYS_PRE_MCLK;
		snd_soc_component_update_bits(component, RT1011_CLK_DET,
			RT1011_EN_MCLK_DET_MASK, RT1011_EN_MCLK_DET);
		break;
	case RT1011_FS_SYS_PRE_S_BCLK:
		reg_val |= RT1011_FS_SYS_PRE_BCLK;
		break;
	case RT1011_FS_SYS_PRE_S_PLL1:
		reg_val |= RT1011_FS_SYS_PRE_PLL1;
		break;
	case RT1011_FS_SYS_PRE_S_RCCLK:
		reg_val |= RT1011_FS_SYS_PRE_RCCLK;
		break;
	default:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, RT1011_CLK_2,
		RT1011_FS_SYS_PRE_MASK, reg_val);
	rt1011->sysclk = freq;
	rt1011->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	return 0;
}