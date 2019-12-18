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
typedef  int u16 ;
struct wm8960_priv {scalar_t__ clk_id; int freq_in; int sysclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8960_CLOCK1 ; 
 int /*<<< orphan*/  WM8960_CLOCK2 ; 
 int /*<<< orphan*/  WM8960_IFACE1 ; 
 scalar_t__ WM8960_SYSCLK_AUTO ; 
 scalar_t__ WM8960_SYSCLK_MCLK ; 
 scalar_t__ WM8960_SYSCLK_PLL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int wm8960_configure_pll (struct snd_soc_component*,int,int*,int*,int*) ; 
 int wm8960_configure_sysclk (struct wm8960_priv*,int,int*,int*,int*) ; 
 int /*<<< orphan*/  wm8960_set_pll (struct snd_soc_component*,int,int) ; 

__attribute__((used)) static int wm8960_configure_clocking(struct snd_soc_component *component)
{
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	int freq_out, freq_in;
	u16 iface1 = snd_soc_component_read32(component, WM8960_IFACE1);
	int i, j, k;
	int ret;

	if (!(iface1 & (1<<6))) {
		dev_dbg(component->dev,
			"Codec is slave mode, no need to configure clock\n");
		return 0;
	}

	if (wm8960->clk_id != WM8960_SYSCLK_MCLK && !wm8960->freq_in) {
		dev_err(component->dev, "No MCLK configured\n");
		return -EINVAL;
	}

	freq_in = wm8960->freq_in;
	/*
	 * If it's sysclk auto mode, check if the MCLK can provide sysclk or
	 * not. If MCLK can provide sysclk, using MCLK to provide sysclk
	 * directly. Otherwise, auto select a available pll out frequency
	 * and set PLL.
	 */
	if (wm8960->clk_id == WM8960_SYSCLK_AUTO) {
		/* disable the PLL and using MCLK to provide sysclk */
		wm8960_set_pll(component, 0, 0);
		freq_out = freq_in;
	} else if (wm8960->sysclk) {
		freq_out = wm8960->sysclk;
	} else {
		dev_err(component->dev, "No SYSCLK configured\n");
		return -EINVAL;
	}

	if (wm8960->clk_id != WM8960_SYSCLK_PLL) {
		ret = wm8960_configure_sysclk(wm8960, freq_out, &i, &j, &k);
		if (ret >= 0) {
			goto configure_clock;
		} else if (wm8960->clk_id != WM8960_SYSCLK_AUTO) {
			dev_err(component->dev, "failed to configure clock\n");
			return -EINVAL;
		}
	}

	freq_out = wm8960_configure_pll(component, freq_in, &i, &j, &k);
	if (freq_out < 0) {
		dev_err(component->dev, "failed to configure clock via PLL\n");
		return freq_out;
	}
	wm8960_set_pll(component, freq_in, freq_out);

configure_clock:
	/* configure sysclk clock */
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 3 << 1, i << 1);

	/* configure frame clock */
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 0x7 << 3, j << 3);
	snd_soc_component_update_bits(component, WM8960_CLOCK1, 0x7 << 6, j << 6);

	/* configure bit clock */
	snd_soc_component_update_bits(component, WM8960_CLOCK2, 0xf, k);

	return 0;
}