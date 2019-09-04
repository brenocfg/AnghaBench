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
struct wm8960_priv {int bclk; int lrclk; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* bclk_divs ; 
 int* dac_divs ; 
 int /*<<< orphan*/  is_pll_freq_available (int,int) ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int* sysclk_divs ; 

__attribute__((used)) static
int wm8960_configure_pll(struct snd_soc_component *component, int freq_in,
			 int *sysclk_idx, int *dac_idx, int *bclk_idx)
{
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	int sysclk, bclk, lrclk, freq_out;
	int diff, closest, best_freq_out;
	int i, j, k;

	bclk = wm8960->bclk;
	lrclk = wm8960->lrclk;
	closest = freq_in;

	best_freq_out = -EINVAL;
	*sysclk_idx = *dac_idx = *bclk_idx = -1;

	for (i = 0; i < ARRAY_SIZE(sysclk_divs); ++i) {
		if (sysclk_divs[i] == -1)
			continue;
		for (j = 0; j < ARRAY_SIZE(dac_divs); ++j) {
			sysclk = lrclk * dac_divs[j];
			freq_out = sysclk * sysclk_divs[i];

			for (k = 0; k < ARRAY_SIZE(bclk_divs); ++k) {
				if (!is_pll_freq_available(freq_in, freq_out))
					continue;

				diff = sysclk - bclk * bclk_divs[k] / 10;
				if (diff == 0) {
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					return freq_out;
				}
				if (diff > 0 && closest > diff) {
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					closest = diff;
					best_freq_out = freq_out;
				}
			}
		}
	}

	return best_freq_out;
}