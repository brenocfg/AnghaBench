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
struct wm8996_priv {int sysclk; int* bclk_rate; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int WM8996_AIF1_BCLK ; 
 int /*<<< orphan*/  WM8996_AIF1_BCLK_DIV_MASK ; 
 int WM8996_AIF2_BCLK ; 
 int WM8996_AIFS ; 
 int* bclk_divs ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wm8996_update_bclk(struct snd_soc_component *component)
{
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	int aif, best, cur_val, bclk_rate, bclk_reg, i;

	/* Don't bother if we're in a low frequency idle mode that
	 * can't support audio.
	 */
	if (wm8996->sysclk < 64000)
		return;

	for (aif = 0; aif < WM8996_AIFS; aif++) {
		switch (aif) {
		case 0:
			bclk_reg = WM8996_AIF1_BCLK;
			break;
		case 1:
			bclk_reg = WM8996_AIF2_BCLK;
			break;
		}

		bclk_rate = wm8996->bclk_rate[aif];

		/* Pick a divisor for BCLK as close as we can get to ideal */
		best = 0;
		for (i = 0; i < ARRAY_SIZE(bclk_divs); i++) {
			cur_val = (wm8996->sysclk / bclk_divs[i]) - bclk_rate;
			if (cur_val < 0) /* BCLK table is sorted */
				break;
			best = i;
		}
		bclk_rate = wm8996->sysclk / bclk_divs[best];
		dev_dbg(component->dev, "Using BCLK_DIV %d for actual BCLK %dHz\n",
			bclk_divs[best], bclk_rate);

		snd_soc_component_update_bits(component, bclk_reg,
				    WM8996_AIF1_BCLK_DIV_MASK, best);
	}
}