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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct _pll_div {int n; int k; scalar_t__ div2; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8991_CLOCKING_2 ; 
 int /*<<< orphan*/  WM8991_PLL1 ; 
 int /*<<< orphan*/  WM8991_PLL2 ; 
 int /*<<< orphan*/  WM8991_PLL3 ; 
 int WM8991_PLL_ENA ; 
 int /*<<< orphan*/  WM8991_POWER_MANAGEMENT_2 ; 
 int WM8991_PRESCALE ; 
 int WM8991_SDM ; 
 int WM8991_SYSCLK_SRC ; 
 int /*<<< orphan*/  pll_factors (struct _pll_div*,unsigned int,unsigned int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8991_set_dai_pll(struct snd_soc_dai *codec_dai,
			      int pll_id, int src, unsigned int freq_in, unsigned int freq_out)
{
	u16 reg;
	struct snd_soc_component *component = codec_dai->component;
	struct _pll_div pll_div;

	if (freq_in && freq_out) {
		pll_factors(&pll_div, freq_out * 4, freq_in);

		/* Turn on PLL */
		reg = snd_soc_component_read32(component, WM8991_POWER_MANAGEMENT_2);
		reg |= WM8991_PLL_ENA;
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_2, reg);

		/* sysclk comes from PLL */
		reg = snd_soc_component_read32(component, WM8991_CLOCKING_2);
		snd_soc_component_write(component, WM8991_CLOCKING_2, reg | WM8991_SYSCLK_SRC);

		/* set up N , fractional mode and pre-divisor if necessary */
		snd_soc_component_write(component, WM8991_PLL1, pll_div.n | WM8991_SDM |
			      (pll_div.div2 ? WM8991_PRESCALE : 0));
		snd_soc_component_write(component, WM8991_PLL2, (u8)(pll_div.k>>8));
		snd_soc_component_write(component, WM8991_PLL3, (u8)(pll_div.k & 0xFF));
	} else {
		/* Turn on PLL */
		reg = snd_soc_component_read32(component, WM8991_POWER_MANAGEMENT_2);
		reg &= ~WM8991_PLL_ENA;
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_2, reg);
	}
	return 0;
}