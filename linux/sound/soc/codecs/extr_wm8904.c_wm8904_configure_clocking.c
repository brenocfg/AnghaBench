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
struct wm8904_priv {int sysclk_src; unsigned int mclk_rate; unsigned int fll_fout; unsigned int sysclk_rate; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8904_CLK_FLL 129 
#define  WM8904_CLK_MCLK 128 
 unsigned int WM8904_CLK_SYS_ENA ; 
 int /*<<< orphan*/  WM8904_CLOCK_RATES_0 ; 
 int /*<<< orphan*/  WM8904_CLOCK_RATES_2 ; 
 int /*<<< orphan*/  WM8904_FLL_CONTROL_1 ; 
 unsigned int WM8904_FLL_ENA ; 
 unsigned int WM8904_FLL_OSC_ENA ; 
 unsigned int WM8904_MCLK_DIV ; 
 unsigned int WM8904_SYSCLK_SRC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm8904_configure_clocking(struct snd_soc_component *component)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	unsigned int clock0, clock2, rate;

	/* Gate the clock while we're updating to avoid misclocking */
	clock2 = snd_soc_component_read32(component, WM8904_CLOCK_RATES_2);
	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
			    WM8904_SYSCLK_SRC, 0);

	/* This should be done on init() for bypass paths */
	switch (wm8904->sysclk_src) {
	case WM8904_CLK_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK\n", wm8904->mclk_rate);

		clock2 &= ~WM8904_SYSCLK_SRC;
		rate = wm8904->mclk_rate;

		/* Ensure the FLL is stopped */
		snd_soc_component_update_bits(component, WM8904_FLL_CONTROL_1,
				    WM8904_FLL_OSC_ENA | WM8904_FLL_ENA, 0);
		break;

	case WM8904_CLK_FLL:
		dev_dbg(component->dev, "Using %dHz FLL clock\n",
			wm8904->fll_fout);

		clock2 |= WM8904_SYSCLK_SRC;
		rate = wm8904->fll_fout;
		break;

	default:
		dev_err(component->dev, "System clock not configured\n");
		return -EINVAL;
	}

	/* SYSCLK shouldn't be over 13.5MHz */
	if (rate > 13500000) {
		clock0 = WM8904_MCLK_DIV;
		wm8904->sysclk_rate = rate / 2;
	} else {
		clock0 = 0;
		wm8904->sysclk_rate = rate;
	}

	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_0, WM8904_MCLK_DIV,
			    clock0);

	snd_soc_component_update_bits(component, WM8904_CLOCK_RATES_2,
			    WM8904_CLK_SYS_ENA | WM8904_SYSCLK_SRC, clock2);

	dev_dbg(component->dev, "CLK_SYS is %dHz\n", wm8904->sysclk_rate);

	return 0;
}