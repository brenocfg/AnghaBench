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
struct wm8960_priv {scalar_t__ lrclk; scalar_t__ deemph; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  WM8960_DACCTL1 ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__* deemph_settings ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8960_set_deemph(struct snd_soc_component *component)
{
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	int val, i, best;

	/* If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	if (wm8960->deemph) {
		best = 1;
		for (i = 2; i < ARRAY_SIZE(deemph_settings); i++) {
			if (abs(deemph_settings[i] - wm8960->lrclk) <
			    abs(deemph_settings[best] - wm8960->lrclk))
				best = i;
		}

		val = best << 1;
	} else {
		val = 0;
	}

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	return snd_soc_component_update_bits(component, WM8960_DACCTL1,
				   0x6, val);
}