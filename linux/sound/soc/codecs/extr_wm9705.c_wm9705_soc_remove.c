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
struct wm9705_priv {int /*<<< orphan*/  ac97; int /*<<< orphan*/  mfd_pdata; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_SOC_AC97_BUS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_exit_regmap (struct snd_soc_component*) ; 
 struct wm9705_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_free_ac97_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm9705_soc_remove(struct snd_soc_component *component)
{
	struct wm9705_priv *wm9705 = snd_soc_component_get_drvdata(component);

	if (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS) && !wm9705->mfd_pdata) {
		snd_soc_component_exit_regmap(component);
		snd_soc_free_ac97_component(wm9705->ac97);
	}
}