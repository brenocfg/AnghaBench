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
struct wm8983_priv {unsigned int sysclk; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8983_CLKSEL ; 
 int /*<<< orphan*/  WM8983_CLKSEL_MASK ; 
#define  WM8983_CLKSRC_MCLK 129 
#define  WM8983_CLKSRC_PLL 128 
 int /*<<< orphan*/  WM8983_CLOCK_GEN_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8983_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8983_set_sysclk(struct snd_soc_dai *dai,
			     int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct wm8983_priv *wm8983 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case WM8983_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
				    WM8983_CLKSEL_MASK, 0);
		break;
	case WM8983_CLKSRC_PLL:
		snd_soc_component_update_bits(component, WM8983_CLOCK_GEN_CONTROL,
				    WM8983_CLKSEL_MASK, WM8983_CLKSEL);
		break;
	default:
		dev_err(dai->dev, "Unknown clock source: %d\n", clk_id);
		return -EINVAL;
	}

	wm8983->sysclk = freq;
	return 0;
}