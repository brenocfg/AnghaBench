#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm8955_priv {int fs; scalar_t__ mclk_rate; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct pll_factors {int n; int k; scalar_t__ outdiv; } ;
struct TYPE_3__ {int fs; scalar_t__ mclk; int usb; int sr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WM8955_CLOCKING_PLL ; 
 int WM8955_KEN ; 
 int WM8955_K_17_9_MASK ; 
 int WM8955_K_21_18_MASK ; 
 int WM8955_K_8_0_MASK ; 
 int WM8955_MCLKSEL ; 
 int WM8955_N_MASK ; 
 int WM8955_N_SHIFT ; 
 int WM8955_PLLEN ; 
 int WM8955_PLLOUTDIV2 ; 
 int /*<<< orphan*/  WM8955_PLL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8955_PLL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8955_PLL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8955_PLL_CONTROL_4 ; 
 int WM8955_PLL_RB ; 
 int /*<<< orphan*/  WM8955_SAMPLE_RATE ; 
 int WM8955_SR_MASK ; 
 int WM8955_SR_SHIFT ; 
 int WM8955_USB ; 
 TYPE_1__* clock_cfgs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct wm8955_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int wm8955_pll_factors (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct pll_factors*) ; 

__attribute__((used)) static int wm8955_configure_clocking(struct snd_soc_component *component)
{
	struct wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	int i, ret, val;
	int clocking = 0;
	int srate = 0;
	int sr = -1;
	struct pll_factors pll;

	/* If we're not running a sample rate currently just pick one */
	if (wm8955->fs == 0)
		wm8955->fs = 8000;

	/* Can we generate an exact output? */
	for (i = 0; i < ARRAY_SIZE(clock_cfgs); i++) {
		if (wm8955->fs != clock_cfgs[i].fs)
			continue;
		sr = i;

		if (wm8955->mclk_rate == clock_cfgs[i].mclk)
			break;
	}

	/* We should never get here with an unsupported sample rate */
	if (sr == -1) {
		dev_err(component->dev, "Sample rate %dHz unsupported\n",
			wm8955->fs);
		WARN_ON(sr == -1);
		return -EINVAL;
	}

	if (i == ARRAY_SIZE(clock_cfgs)) {
		/* If we can't generate the right clock from MCLK then
		 * we should configure the PLL to supply us with an
		 * appropriate clock.
		 */
		clocking |= WM8955_MCLKSEL;

		/* Use the last divider configuration we saw for the
		 * sample rate. */
		ret = wm8955_pll_factors(component->dev, wm8955->mclk_rate,
					 clock_cfgs[sr].mclk, &pll);
		if (ret != 0) {
			dev_err(component->dev,
				"Unable to generate %dHz from %dHz MCLK\n",
				wm8955->fs, wm8955->mclk_rate);
			return -EINVAL;
		}

		snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_1,
				    WM8955_N_MASK | WM8955_K_21_18_MASK,
				    (pll.n << WM8955_N_SHIFT) |
				    pll.k >> 18);
		snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_2,
				    WM8955_K_17_9_MASK,
				    (pll.k >> 9) & WM8955_K_17_9_MASK);
		snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_3,
				    WM8955_K_8_0_MASK,
				    pll.k & WM8955_K_8_0_MASK);
		if (pll.k)
			snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_4,
					    WM8955_KEN, WM8955_KEN);
		else
			snd_soc_component_update_bits(component, WM8955_PLL_CONTROL_4,
					    WM8955_KEN, 0);

		if (pll.outdiv)
			val = WM8955_PLL_RB | WM8955_PLLOUTDIV2;
		else
			val = WM8955_PLL_RB;

		/* Now start the PLL running */
		snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
				    WM8955_PLL_RB | WM8955_PLLOUTDIV2, val);
		snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
				    WM8955_PLLEN, WM8955_PLLEN);
	}

	srate = clock_cfgs[sr].usb | (clock_cfgs[sr].sr << WM8955_SR_SHIFT);

	snd_soc_component_update_bits(component, WM8955_SAMPLE_RATE,
			    WM8955_USB | WM8955_SR_MASK, srate);
	snd_soc_component_update_bits(component, WM8955_CLOCKING_PLL,
			    WM8955_MCLKSEL, clocking);

	return 0;
}