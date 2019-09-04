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
struct wm8904_priv {scalar_t__ fs; scalar_t__ deemph; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  WM8904_DAC_DIGITAL_1 ; 
 int /*<<< orphan*/  WM8904_DEEMPH_MASK ; 
 int WM8904_DEEMPH_SHIFT ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__* deemph_settings ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8904_set_deemph(struct snd_soc_component *component)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	int val, i, best;

	/* If we're using deemphasis select the nearest available sample 
	 * rate.
	 */
	if (wm8904->deemph) {
		best = 1;
		for (i = 2; i < ARRAY_SIZE(deemph_settings); i++) {
			if (abs(deemph_settings[i] - wm8904->fs) <
			    abs(deemph_settings[best] - wm8904->fs))
				best = i;
		}

		val = best << WM8904_DEEMPH_SHIFT;
	} else {
		val = 0;
	}

	dev_dbg(component->dev, "Set deemphasis %d\n", val);

	return snd_soc_component_update_bits(component, WM8904_DAC_DIGITAL_1,
				   WM8904_DEEMPH_MASK, val);
}