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
typedef  int u64 ;
struct wm8978_pll_div {int div2; unsigned int n; unsigned int k; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long long FIXED_PLL_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 

__attribute__((used)) static void pll_factors(struct snd_soc_component *component,
		struct wm8978_pll_div *pll_div, unsigned int target, unsigned int source)
{
	u64 k_part;
	unsigned int k, n_div, n_mod;

	n_div = target / source;
	if (n_div < 6) {
		source >>= 1;
		pll_div->div2 = 1;
		n_div = target / source;
	} else {
		pll_div->div2 = 0;
	}

	if (n_div < 6 || n_div > 12)
		dev_warn(component->dev,
			 "WM8978 N value exceeds recommended range! N = %u\n",
			 n_div);

	pll_div->n = n_div;
	n_mod = target - source * n_div;
	k_part = FIXED_PLL_SIZE * (long long)n_mod + source / 2;

	do_div(k_part, source);

	k = k_part & 0xFFFFFFFF;

	pll_div->k = k;
}