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
struct wm8737_priv {int /*<<< orphan*/  supplies; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM8737_LEFT_PGA_VOLUME ; 
 int /*<<< orphan*/  WM8737_LVU ; 
 int /*<<< orphan*/  WM8737_RIGHT_PGA_VOLUME ; 
 int /*<<< orphan*/  WM8737_RVU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct wm8737_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm8737_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8737_probe(struct snd_soc_component *component)
{
	struct wm8737_priv *wm8737 = snd_soc_component_get_drvdata(component);
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8737->supplies),
				    wm8737->supplies);
	if (ret != 0) {
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		goto err_get;
	}

	ret = wm8737_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset\n");
		goto err_enable;
	}

	snd_soc_component_update_bits(component, WM8737_LEFT_PGA_VOLUME, WM8737_LVU,
			    WM8737_LVU);
	snd_soc_component_update_bits(component, WM8737_RIGHT_PGA_VOLUME, WM8737_RVU,
			    WM8737_RVU);

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Bias level configuration will have done an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(wm8737->supplies), wm8737->supplies);

	return 0;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8737->supplies), wm8737->supplies);
err_get:
	return ret;
}