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
struct snd_soc_component {int dummy; } ;
struct aic3x_priv {unsigned int sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC3X_CLKGEN_CTRL_REG ; 
 int /*<<< orphan*/  CLKDIV_IN_MASK ; 
 int CLKDIV_IN_SHIFT ; 
 int /*<<< orphan*/  PLLCLK_IN_MASK ; 
 int PLLCLK_IN_SHIFT ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic3x_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	/* set clock on MCLK or GPIO2 or BCLK */
	snd_soc_component_update_bits(component, AIC3X_CLKGEN_CTRL_REG, PLLCLK_IN_MASK,
				clk_id << PLLCLK_IN_SHIFT);
	snd_soc_component_update_bits(component, AIC3X_CLKGEN_CTRL_REG, CLKDIV_IN_MASK,
				clk_id << CLKDIV_IN_SHIFT);

	aic3x->sysclk = freq;
	return 0;
}