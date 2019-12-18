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
struct tscs42xx {int /*<<< orphan*/  pll_lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RM_PLLCTL1C_PDB_PLL1 ; 
 int /*<<< orphan*/  RM_PLLCTL1C_PDB_PLL2 ; 
 int /*<<< orphan*/  RV_PLLCTL1C_PDB_PLL1_DISABLE ; 
 int /*<<< orphan*/  RV_PLLCTL1C_PDB_PLL2_DISABLE ; 
 int /*<<< orphan*/  R_PLLCTL1C ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tscs42xx* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int power_down_audio_plls(struct snd_soc_component *component)
{
	struct tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	int ret;

	mutex_lock(&tscs42xx->pll_lock);

	ret = snd_soc_component_update_bits(component, R_PLLCTL1C,
			RM_PLLCTL1C_PDB_PLL1,
			RV_PLLCTL1C_PDB_PLL1_DISABLE);
	if (ret < 0) {
		dev_err(component->dev, "Failed to turn PLL off (%d)\n", ret);
		goto exit;
	}
	ret = snd_soc_component_update_bits(component, R_PLLCTL1C,
			RM_PLLCTL1C_PDB_PLL2,
			RV_PLLCTL1C_PDB_PLL2_DISABLE);
	if (ret < 0) {
		dev_err(component->dev, "Failed to turn PLL off (%d)\n", ret);
		goto exit;
	}

	ret = 0;
exit:
	mutex_unlock(&tscs42xx->pll_lock);

	return ret;
}