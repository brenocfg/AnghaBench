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
struct wm8900_priv {int fll_out; int fll_in; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct wm8900_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8900_reset (struct snd_soc_component*) ; 
 int wm8900_set_fll (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8900_resume(struct snd_soc_component *component)
{
	struct wm8900_priv *wm8900 = snd_soc_component_get_drvdata(component);
	int ret;

	wm8900_reset(component);

	ret = regcache_sync(wm8900->regmap);
	if (ret != 0) {
		dev_err(component->dev, "Failed to restore cache: %d\n", ret);
		return ret;
	}

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Restart the FLL? */
	if (wm8900->fll_out) {
		int fll_out = wm8900->fll_out;
		int fll_in  = wm8900->fll_in;

		wm8900->fll_in = 0;
		wm8900->fll_out = 0;

		ret = wm8900_set_fll(component, 0, fll_in, fll_out);
		if (ret != 0) {
			dev_err(component->dev, "Failed to restart FLL\n");
			return ret;
		}
	}

	return 0;
}