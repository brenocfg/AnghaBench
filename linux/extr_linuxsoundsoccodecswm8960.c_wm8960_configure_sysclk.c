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

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* bclk_divs ; 
 int* dac_divs ; 
 int* sysclk_divs ; 

__attribute__((used)) static
int wm8960_configure_sysclk(struct wm8960_priv *wm8960, int mclk,
			    int *sysclk_idx, int *dac_idx, int *bclk_idx)
{
	int sysclk, bclk, lrclk;
	int i, j, k;
	int diff, closest = mclk;

	/* marker for no match */
	*bclk_idx = -1;

	bclk = wm8960->bclk;
	lrclk = wm8960->lrclk;

	/* check if the sysclk frequency is available. */
	for (i = 0; i < ARRAY_SIZE(sysclk_divs); ++i) {
		if (sysclk_divs[i] == -1)
			continue;
		sysclk = mclk / sysclk_divs[i];
		for (j = 0; j < ARRAY_SIZE(dac_divs); ++j) {
			if (sysclk != dac_divs[j] * lrclk)
				continue;
			for (k = 0; k < ARRAY_SIZE(bclk_divs); ++k) {
				diff = sysclk - bclk * bclk_divs[k] / 10;
				if (diff == 0) {
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					break;
				}
				if (diff > 0 && closest > diff) {
					*sysclk_idx = i;
					*dac_idx = j;
					*bclk_idx = k;
					closest = diff;
				}
			}
			if (k != ARRAY_SIZE(bclk_divs))
				break;
		}
		if (j != ARRAY_SIZE(dac_divs))
			break;
	}
	return *bclk_idx;
}