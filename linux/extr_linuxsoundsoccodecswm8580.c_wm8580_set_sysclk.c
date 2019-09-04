#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wm8580_priv {unsigned int* sysclk; } ;
struct snd_soc_dai {TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WM8580_CLKSEL ; 
#define  WM8580_CLKSRC_ADCMCLK 133 
#define  WM8580_CLKSRC_MCLK 132 
#define  WM8580_CLKSRC_PLLA 131 
#define  WM8580_CLKSRC_PLLB 130 
#define  WM8580_DAI_PAIFRX 129 
#define  WM8580_DAI_PAIFTX 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8580_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8580_set_sysclk(struct snd_soc_dai *dai, int clk_id,
			     unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	int ret, sel, sel_mask, sel_shift;

	switch (dai->driver->id) {
	case WM8580_DAI_PAIFRX:
		sel_mask = 0x3;
		sel_shift = 0;
		break;

	case WM8580_DAI_PAIFTX:
		sel_mask = 0xc;
		sel_shift = 2;
		break;

	default:
		WARN(1, "Unknown DAI driver ID\n");
		return -EINVAL;
	}

	switch (clk_id) {
	case WM8580_CLKSRC_ADCMCLK:
		if (dai->driver->id != WM8580_DAI_PAIFTX)
			return -EINVAL;
		sel = 0 << sel_shift;
		break;
	case WM8580_CLKSRC_PLLA:
		sel = 1 << sel_shift;
		break;
	case WM8580_CLKSRC_PLLB:
		sel = 2 << sel_shift;
		break;
	case WM8580_CLKSRC_MCLK:
		sel = 3 << sel_shift;
		break;
	default:
		dev_err(component->dev, "Unknown clock %d\n", clk_id);
		return -EINVAL;
	}

	/* We really should validate PLL settings but not yet */
	wm8580->sysclk[dai->driver->id] = freq;

	ret = snd_soc_component_update_bits(component, WM8580_CLKSEL, sel_mask, sel);
	if (ret < 0)
		return ret;

	return 0;
}