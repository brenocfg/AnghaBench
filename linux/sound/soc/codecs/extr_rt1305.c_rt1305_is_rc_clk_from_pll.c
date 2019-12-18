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
struct rt1305_priv {scalar_t__ sysclk_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT1305_CLK_1 ; 
 scalar_t__ RT1305_FS_SYS_PRE_S_PLL1 ; 
 unsigned int RT1305_SEL_PLL_SRC_2_RCCLK ; 
 struct rt1305_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_read (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt1305_is_rc_clk_from_pll(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	struct rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	snd_soc_component_read(component, RT1305_CLK_1, &val);

	if (rt1305->sysclk_src == RT1305_FS_SYS_PRE_S_PLL1 &&
		(val & RT1305_SEL_PLL_SRC_2_RCCLK))
		return 1;
	else
		return 0;
}