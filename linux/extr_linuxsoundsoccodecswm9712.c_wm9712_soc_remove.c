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

/* Variables and functions */

__attribute__((used)) static void wm9712_soc_remove(struct snd_soc_component *component)
{
#ifdef CONFIG_SND_SOC_AC97_BUS
	struct wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);

	if (!wm9712->mfd_pdata) {
		snd_soc_component_exit_regmap(component);
		snd_soc_free_ac97_component(wm9712->ac97);
	}
#endif
}