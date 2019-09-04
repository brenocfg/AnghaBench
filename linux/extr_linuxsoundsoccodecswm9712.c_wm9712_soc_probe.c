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
struct wm9712_priv {TYPE_1__* mfd_pdata; int /*<<< orphan*/  ac97; } ;
struct snd_soc_component {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_VIDEO ; 
 struct wm9712_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,struct regmap*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm9712_soc_probe(struct snd_soc_component *component)
{
	struct wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);
	struct regmap *regmap;
	int ret;

	if (wm9712->mfd_pdata) {
		wm9712->ac97 = wm9712->mfd_pdata->ac97;
		regmap = wm9712->mfd_pdata->regmap;
	} else {
#ifdef CONFIG_SND_SOC_AC97_BUS
		wm9712->ac97 = snd_soc_new_ac97_component(component, WM9712_VENDOR_ID,
						      WM9712_VENDOR_ID_MASK);
		if (IS_ERR(wm9712->ac97)) {
			ret = PTR_ERR(wm9712->ac97);
			dev_err(component->dev,
				"Failed to register AC97 codec: %d\n", ret);
			return ret;
		}

		regmap = regmap_init_ac97(wm9712->ac97, &wm9712_regmap_config);
		if (IS_ERR(regmap)) {
			snd_soc_free_ac97_component(wm9712->ac97);
			return PTR_ERR(regmap);
		}
#endif
	}

	snd_soc_component_init_regmap(component, regmap);

	/* set alc mux to none */
	snd_soc_component_update_bits(component, AC97_VIDEO, 0x3000, 0x3000);

	return 0;
}