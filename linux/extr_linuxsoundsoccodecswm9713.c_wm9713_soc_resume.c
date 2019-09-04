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
struct wm9713_priv {scalar_t__ pll_in; int /*<<< orphan*/  ac97; } ;
struct snd_soc_component {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM9713_VENDOR_ID ; 
 int /*<<< orphan*/  WM9713_VENDOR_ID_MASK ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int snd_ac97_reset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_cache_sync (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct wm9713_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm9713_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm9713_soc_resume(struct snd_soc_component *component)
{
	struct wm9713_priv *wm9713 = snd_soc_component_get_drvdata(component);
	int ret;

	ret = snd_ac97_reset(wm9713->ac97, true, WM9713_VENDOR_ID,
		WM9713_VENDOR_ID_MASK);
	if (ret < 0)
		return ret;

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* do we need to re-start the PLL ? */
	if (wm9713->pll_in)
		wm9713_set_pll(component, 0, wm9713->pll_in, 0);

	/* only synchronise the codec if warm reset failed */
	if (ret == 0) {
		regcache_mark_dirty(component->regmap);
		snd_soc_component_cache_sync(component);
	}

	return ret;
}