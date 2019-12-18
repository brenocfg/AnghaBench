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
struct wm8900_priv {int fll_out; int fll_in; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct wm8900_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int wm8900_set_fll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8900_suspend(struct snd_soc_component *component)
{
	struct wm8900_priv *wm8900 = snd_soc_component_get_drvdata(component);
	int fll_out = wm8900->fll_out;
	int fll_in  = wm8900->fll_in;
	int ret;

	/* Stop the FLL in an orderly fashion */
	ret = wm8900_set_fll(component, 0, 0, 0);
	if (ret != 0) {
		dev_err(component->dev, "Failed to stop FLL\n");
		return ret;
	}

	wm8900->fll_out = fll_out;
	wm8900->fll_in = fll_in;

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_OFF);

	return 0;
}