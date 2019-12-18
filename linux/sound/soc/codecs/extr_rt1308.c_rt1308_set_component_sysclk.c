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
struct rt1308_priv {unsigned int sysclk; int sysclk_src; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT1308_CLK_1 ; 
 int /*<<< orphan*/  RT1308_CLK_DET ; 
#define  RT1308_FS_SYS_S_BCLK 131 
#define  RT1308_FS_SYS_S_MCLK 130 
#define  RT1308_FS_SYS_S_PLL 129 
#define  RT1308_FS_SYS_S_RCCLK 128 
 unsigned int RT1308_MCLK_DET_EN ; 
 int /*<<< orphan*/  RT1308_MCLK_DET_EN_MASK ; 
 int /*<<< orphan*/  RT1308_SEL_FS_SYS_MASK ; 
 unsigned int RT1308_SEL_FS_SYS_SRC_BCLK ; 
 unsigned int RT1308_SEL_FS_SYS_SRC_MCLK ; 
 unsigned int RT1308_SEL_FS_SYS_SRC_PLL ; 
 unsigned int RT1308_SEL_FS_SYS_SRC_RCCLK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rt1308_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int rt1308_set_component_sysclk(struct snd_soc_component *component,
		int clk_id, int source, unsigned int freq, int dir)
{
	struct rt1308_priv *rt1308 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;

	if (freq == rt1308->sysclk && clk_id == rt1308->sysclk_src)
		return 0;

	switch (clk_id) {
	case RT1308_FS_SYS_S_MCLK:
		reg_val |= RT1308_SEL_FS_SYS_SRC_MCLK;
		snd_soc_component_update_bits(component,
			RT1308_CLK_DET, RT1308_MCLK_DET_EN_MASK,
			RT1308_MCLK_DET_EN);
		break;
	case RT1308_FS_SYS_S_BCLK:
		reg_val |= RT1308_SEL_FS_SYS_SRC_BCLK;
		break;
	case RT1308_FS_SYS_S_PLL:
		reg_val |= RT1308_SEL_FS_SYS_SRC_PLL;
		break;
	case RT1308_FS_SYS_S_RCCLK:
		reg_val |= RT1308_SEL_FS_SYS_SRC_RCCLK;
		break;
	default:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, RT1308_CLK_1,
		RT1308_SEL_FS_SYS_MASK, reg_val);
	rt1308->sysclk = freq;
	rt1308->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	return 0;
}