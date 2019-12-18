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

/* Variables and functions */
 int /*<<< orphan*/  RT5659_GLB_CLK ; 
 unsigned int RT5659_SCLK_SRC_MASK ; 
 unsigned int RT5659_SCLK_SRC_PLL1 ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_sys_clk_from_pll(struct snd_soc_dapm_widget *w,
			 struct snd_soc_dapm_widget *sink)
{
	unsigned int val;
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	val = snd_soc_component_read32(component, RT5659_GLB_CLK);
	val &= RT5659_SCLK_SRC_MASK;
	if (val == RT5659_SCLK_SRC_PLL1)
		return 1;
	else
		return 0;
}