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
struct wm8741_priv {int /*<<< orphan*/  supplies; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm8741_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int wm8741_add_controls (struct snd_soc_component*) ; 
 int wm8741_configure (struct snd_soc_component*) ; 
 int wm8741_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8741_probe(struct snd_soc_component *component)
{
	struct wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8741->supplies),
				    wm8741->supplies);
	if (ret != 0) {
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		goto err_get;
	}

	ret = wm8741_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset\n");
		goto err_enable;
	}

	ret = wm8741_configure(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to change default settings\n");
		goto err_enable;
	}

	ret = wm8741_add_controls(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to add controls\n");
		goto err_enable;
	}

	dev_dbg(component->dev, "Successful registration\n");
	return ret;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8741->supplies), wm8741->supplies);
err_get:
	return ret;
}