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
struct snd_soc_component {int dummy; } ;
struct da7219_priv {int /*<<< orphan*/  supplies; scalar_t__* dai_clks_lookup; } ;

/* Variables and functions */
 int DA7219_DAI_NUM_CLKS ; 
 int /*<<< orphan*/  DA7219_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clkdev_drop (scalar_t__) ; 
 int /*<<< orphan*/  da7219_aad_exit (struct snd_soc_component*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void da7219_remove(struct snd_soc_component *component)
{
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
#ifdef CONFIG_COMMON_CLK
	int i;
#endif

	da7219_aad_exit(component);

#ifdef CONFIG_COMMON_CLK
	for (i = DA7219_DAI_NUM_CLKS - 1; i >= 0; --i) {
		if (da7219->dai_clks_lookup[i])
			clkdev_drop(da7219->dai_clks_lookup[i]);
	}
#endif

	/* Supplies */
	regulator_bulk_disable(DA7219_NUM_SUPPLIES, da7219->supplies);
}