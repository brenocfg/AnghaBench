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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct pll_div {int div2; int n; int k; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8985_CLKSEL ; 
 int /*<<< orphan*/  WM8985_CLKSEL_MASK ; 
 int /*<<< orphan*/  WM8985_CLOCK_GEN_CONTROL ; 
 int /*<<< orphan*/  WM8985_PLLEN ; 
 int /*<<< orphan*/  WM8985_PLLEN_MASK ; 
 int /*<<< orphan*/  WM8985_PLL_K_1 ; 
 int /*<<< orphan*/  WM8985_PLL_K_2 ; 
 int /*<<< orphan*/  WM8985_PLL_K_3 ; 
 int /*<<< orphan*/  WM8985_PLL_N ; 
 int WM8985_PLL_PRESCALE_SHIFT ; 
 int /*<<< orphan*/  WM8985_POWER_MANAGEMENT_1 ; 
 int pll_factors (struct pll_div*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8985_set_pll(struct snd_soc_dai *dai, int pll_id,
			  int source, unsigned int freq_in,
			  unsigned int freq_out)
{
	int ret;
	struct snd_soc_component *component;
	struct pll_div pll_div;

	component = dai->component;
	if (!freq_in || !freq_out) {
		/* disable the PLL */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_PLLEN_MASK, 0);
	} else {
		ret = pll_factors(&pll_div, freq_out * 4 * 2, freq_in);
		if (ret)
			return ret;

		/* set PLLN and PRESCALE */
		snd_soc_component_write(component, WM8985_PLL_N,
			      (pll_div.div2 << WM8985_PLL_PRESCALE_SHIFT)
			      | pll_div.n);
		/* set PLLK */
		snd_soc_component_write(component, WM8985_PLL_K_3, pll_div.k & 0x1ff);
		snd_soc_component_write(component, WM8985_PLL_K_2, (pll_div.k >> 9) & 0x1ff);
		snd_soc_component_write(component, WM8985_PLL_K_1, (pll_div.k >> 18));
		/* set the source of the clock to be the PLL */
		snd_soc_component_update_bits(component, WM8985_CLOCK_GEN_CONTROL,
				    WM8985_CLKSEL_MASK, WM8985_CLKSEL);
		/* enable the PLL */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_PLLEN_MASK, WM8985_PLLEN);
	}
	return 0;
}