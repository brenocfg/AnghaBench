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
struct wm8962_priv {int sysclk_rate; int bclk; int lrclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ SND_SOC_BIAS_ON ; 
 int /*<<< orphan*/  WM8962_AIF_RATE_MASK ; 
 int /*<<< orphan*/  WM8962_AUDIO_INTERFACE_2 ; 
 int /*<<< orphan*/  WM8962_BCLK_DIV_MASK ; 
 int /*<<< orphan*/  WM8962_CLOCKING1 ; 
 int /*<<< orphan*/  WM8962_CLOCKING2 ; 
 int /*<<< orphan*/  WM8962_CLOCKING_4 ; 
 int WM8962_DSPCLK_DIV_MASK ; 
 int WM8962_DSPCLK_DIV_SHIFT ; 
 int WM8962_SYSCLK_ENA ; 
 int /*<<< orphan*/  WM8962_SYSCLK_ENA_MASK ; 
 int /*<<< orphan*/  WM8962_SYSCLK_RATE_MASK ; 
 int WM8962_SYSCLK_RATE_SHIFT ; 
 int* bclk_divs ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8962_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* sysclk_rates ; 

__attribute__((used)) static void wm8962_configure_bclk(struct snd_soc_component *component)
{
	struct wm8962_priv *wm8962 = snd_soc_component_get_drvdata(component);
	int dspclk, i;
	int clocking2 = 0;
	int clocking4 = 0;
	int aif2 = 0;

	if (!wm8962->sysclk_rate) {
		dev_dbg(component->dev, "No SYSCLK configured\n");
		return;
	}

	if (!wm8962->bclk || !wm8962->lrclk) {
		dev_dbg(component->dev, "No audio clocks configured\n");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(sysclk_rates); i++) {
		if (sysclk_rates[i] == wm8962->sysclk_rate / wm8962->lrclk) {
			clocking4 |= i << WM8962_SYSCLK_RATE_SHIFT;
			break;
		}
	}

	if (i == ARRAY_SIZE(sysclk_rates)) {
		dev_err(component->dev, "Unsupported sysclk ratio %d\n",
			wm8962->sysclk_rate / wm8962->lrclk);
		return;
	}

	dev_dbg(component->dev, "Selected sysclk ratio %d\n", sysclk_rates[i]);

	snd_soc_component_update_bits(component, WM8962_CLOCKING_4,
			    WM8962_SYSCLK_RATE_MASK, clocking4);

	/* DSPCLK_DIV can be only generated correctly after enabling SYSCLK.
	 * So we here provisionally enable it and then disable it afterward
	 * if current bias_level hasn't reached SND_SOC_BIAS_ON.
	 */
	if (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_ON)
		snd_soc_component_update_bits(component, WM8962_CLOCKING2,
				WM8962_SYSCLK_ENA_MASK, WM8962_SYSCLK_ENA);

	dspclk = snd_soc_component_read32(component, WM8962_CLOCKING1);

	if (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_ON)
		snd_soc_component_update_bits(component, WM8962_CLOCKING2,
				WM8962_SYSCLK_ENA_MASK, 0);

	if (dspclk < 0) {
		dev_err(component->dev, "Failed to read DSPCLK: %d\n", dspclk);
		return;
	}

	dspclk = (dspclk & WM8962_DSPCLK_DIV_MASK) >> WM8962_DSPCLK_DIV_SHIFT;
	switch (dspclk) {
	case 0:
		dspclk = wm8962->sysclk_rate;
		break;
	case 1:
		dspclk = wm8962->sysclk_rate / 2;
		break;
	case 2:
		dspclk = wm8962->sysclk_rate / 4;
		break;
	default:
		dev_warn(component->dev, "Unknown DSPCLK divisor read back\n");
		dspclk = wm8962->sysclk_rate;
	}

	dev_dbg(component->dev, "DSPCLK is %dHz, BCLK %d\n", dspclk, wm8962->bclk);

	/* We're expecting an exact match */
	for (i = 0; i < ARRAY_SIZE(bclk_divs); i++) {
		if (bclk_divs[i] < 0)
			continue;

		if (dspclk / bclk_divs[i] == wm8962->bclk) {
			dev_dbg(component->dev, "Selected BCLK_DIV %d for %dHz\n",
				bclk_divs[i], wm8962->bclk);
			clocking2 |= i;
			break;
		}
	}
	if (i == ARRAY_SIZE(bclk_divs)) {
		dev_err(component->dev, "Unsupported BCLK ratio %d\n",
			dspclk / wm8962->bclk);
		return;
	}

	aif2 |= wm8962->bclk / wm8962->lrclk;
	dev_dbg(component->dev, "Selected LRCLK divisor %d for %dHz\n",
		wm8962->bclk / wm8962->lrclk, wm8962->lrclk);

	snd_soc_component_update_bits(component, WM8962_CLOCKING2,
			    WM8962_BCLK_DIV_MASK, clocking2);
	snd_soc_component_update_bits(component, WM8962_AUDIO_INTERFACE_2,
			    WM8962_AIF_RATE_MASK, aif2);
}