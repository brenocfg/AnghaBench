#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wm9713_priv {TYPE_1__* mfd_pdata; int /*<<< orphan*/  ac97; } ;
struct snd_soc_component {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CD ; 
 struct wm9713_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,struct regmap*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm9713_soc_probe(struct snd_soc_component *component)
{
	struct wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	struct regmap *regmap = NULL;

	if (wm9713->mfd_pdata) {
		wm9713->ac97 = wm9713->mfd_pdata->ac97;
		regmap = wm9713->mfd_pdata->regmap;
	} else {
#ifdef CONFIG_SND_SOC_AC97_BUS
		wm9713->ac97 = snd_soc_new_ac97_component(component, WM9713_VENDOR_ID,
						      WM9713_VENDOR_ID_MASK);
		if (IS_ERR(wm9713->ac97))
			return PTR_ERR(wm9713->ac97);
		regmap = regmap_init_ac97(wm9713->ac97, &wm9713_regmap_config);
		if (IS_ERR(regmap)) {
			snd_soc_free_ac97_component(wm9713->ac97);
			return PTR_ERR(regmap);
		}
#endif
	}

	snd_soc_component_init_regmap(component, regmap);

	/* unmute the adc - move to kcontrol */
	snd_soc_component_update_bits(component, AC97_CD, 0x7fff, 0x0000);

	return 0;
}