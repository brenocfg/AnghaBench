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
struct wm9705_priv {int /*<<< orphan*/  ac97; TYPE_1__* mfd_pdata; } ;
struct snd_soc_component {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 struct wm9705_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,struct regmap*) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm9705_soc_probe(struct snd_soc_component *component)
{
	struct wm9705_priv *wm9705 = snd_soc_component_get_drvdata(component);
	struct regmap *regmap;

	if (wm9705->mfd_pdata) {
		wm9705->ac97 = wm9705->mfd_pdata->ac97;
		regmap = wm9705->mfd_pdata->regmap;
	} else {
#ifdef CONFIG_SND_SOC_AC97_BUS
		wm9705->ac97 = snd_soc_new_ac97_component(component, WM9705_VENDOR_ID,
						      WM9705_VENDOR_ID_MASK);
		if (IS_ERR(wm9705->ac97)) {
			dev_err(component->dev, "Failed to register AC97 codec\n");
			return PTR_ERR(wm9705->ac97);
		}

		regmap = regmap_init_ac97(wm9705->ac97, &wm9705_regmap_config);
		if (IS_ERR(regmap)) {
			snd_soc_free_ac97_component(wm9705->ac97);
			return PTR_ERR(regmap);
		}
#endif
	}

	snd_soc_component_set_drvdata(component, wm9705->ac97);
	snd_soc_component_init_regmap(component, regmap);

	return 0;
}