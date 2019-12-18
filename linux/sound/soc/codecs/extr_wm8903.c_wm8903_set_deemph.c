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
struct wm8903_priv {scalar_t__ fs; scalar_t__ deemph; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  WM8903_DAC_DIGITAL_1 ; 
 int /*<<< orphan*/  WM8903_DEEMPH_MASK ; 
 int WM8903_DEEMPH_SHIFT ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 struct wm8903_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* wm8903_deemph ; 

__attribute__((used)) static int wm8903_set_deemph(struct snd_soc_component *component)
{
	struct wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	int val, i, best;

	/* If we're using deemphasis select the nearest available sample
	 * rate.
	 */
	if (wm8903->deemph) {
		best = 1;
		for (i = 2; i < ARRAY_SIZE(wm8903_deemph); i++) {
			if (abs(wm8903_deemph[i] - wm8903->fs) <
			    abs(wm8903_deemph[best] - wm8903->fs))
				best = i;
		}

		val = best << WM8903_DEEMPH_SHIFT;
	} else {
		best = 0;
		val = 0;
	}

	dev_dbg(component->dev, "Set deemphasis %d (%dHz)\n",
		best, wm8903_deemph[best]);

	return snd_soc_component_update_bits(component, WM8903_DAC_DIGITAL_1,
				   WM8903_DEEMPH_MASK, val);
}