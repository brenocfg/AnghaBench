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
struct wm8804_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  mclk_div; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct pll_div {int n; int prescale; int freqmode; int mclkdiv; int k; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8804_PLL1 ; 
 int /*<<< orphan*/  WM8804_PLL2 ; 
 int /*<<< orphan*/  WM8804_PLL3 ; 
 int /*<<< orphan*/  WM8804_PLL4 ; 
 int /*<<< orphan*/  WM8804_PLL5 ; 
 int /*<<< orphan*/  WM8804_PWRDN ; 
 int pll_factors (struct pll_div*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 struct wm8804_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8804_set_pll(struct snd_soc_dai *dai, int pll_id,
			  int source, unsigned int freq_in,
			  unsigned int freq_out)
{
	struct snd_soc_component *component = dai->component;
	struct wm8804_priv *wm8804 = snd_soc_component_get_drvdata(component);
	bool change;

	if (!freq_in || !freq_out) {
		/* disable the PLL */
		regmap_update_bits_check(wm8804->regmap, WM8804_PWRDN,
					 0x1, 0x1, &change);
		if (change)
			pm_runtime_put(wm8804->dev);
	} else {
		int ret;
		struct pll_div pll_div;

		ret = pll_factors(&pll_div, freq_out, freq_in,
				  wm8804->mclk_div);
		if (ret)
			return ret;

		/* power down the PLL before reprogramming it */
		regmap_update_bits_check(wm8804->regmap, WM8804_PWRDN,
					 0x1, 0x1, &change);
		if (!change)
			pm_runtime_get_sync(wm8804->dev);

		/* set PLLN and PRESCALE */
		snd_soc_component_update_bits(component, WM8804_PLL4, 0xf | 0x10,
				    pll_div.n | (pll_div.prescale << 4));
		/* set mclkdiv and freqmode */
		snd_soc_component_update_bits(component, WM8804_PLL5, 0x3 | 0x8,
				    pll_div.freqmode | (pll_div.mclkdiv << 3));
		/* set PLLK */
		snd_soc_component_write(component, WM8804_PLL1, pll_div.k & 0xff);
		snd_soc_component_write(component, WM8804_PLL2, (pll_div.k >> 8) & 0xff);
		snd_soc_component_write(component, WM8804_PLL3, pll_div.k >> 16);

		/* power up the PLL */
		snd_soc_component_update_bits(component, WM8804_PWRDN, 0x1, 0);
	}

	return 0;
}