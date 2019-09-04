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
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct _pll_div {int n; int k; scalar_t__ div2; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8990_CLOCKING_2 ; 
 int /*<<< orphan*/  WM8990_PLL1 ; 
 int /*<<< orphan*/  WM8990_PLL2 ; 
 int /*<<< orphan*/  WM8990_PLL3 ; 
 int /*<<< orphan*/  WM8990_PLL_ENA ; 
 int /*<<< orphan*/  WM8990_POWER_MANAGEMENT_2 ; 
 int WM8990_PRESCALE ; 
 int WM8990_SDM ; 
 int /*<<< orphan*/  WM8990_SYSCLK_SRC ; 
 int /*<<< orphan*/  pll_factors (struct _pll_div*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8990_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
		int source, unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_component *component = codec_dai->component;
	struct _pll_div pll_div;

	if (freq_in && freq_out) {
		pll_factors(&pll_div, freq_out * 4, freq_in);

		/* Turn on PLL */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_2,
				    WM8990_PLL_ENA, WM8990_PLL_ENA);

		/* sysclk comes from PLL */
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_SYSCLK_SRC, WM8990_SYSCLK_SRC);

		/* set up N , fractional mode and pre-divisor if necessary */
		snd_soc_component_write(component, WM8990_PLL1, pll_div.n | WM8990_SDM |
			(pll_div.div2?WM8990_PRESCALE:0));
		snd_soc_component_write(component, WM8990_PLL2, (u8)(pll_div.k>>8));
		snd_soc_component_write(component, WM8990_PLL3, (u8)(pll_div.k & 0xFF));
	} else {
		/* Turn off PLL */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_2,
				    WM8990_PLL_ENA, 0);
	}
	return 0;
}