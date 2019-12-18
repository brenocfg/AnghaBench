#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8523_priv {int sysclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int ratio; int value; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WM8523_AIF_CTRL1 ; 
 int /*<<< orphan*/  WM8523_AIF_CTRL2 ; 
 int WM8523_AIF_MSTR ; 
 int WM8523_BCLKDIV_MASK ; 
 int WM8523_BCLKDIV_SHIFT ; 
 int WM8523_SR_MASK ; 
 int WM8523_WL_MASK ; 
 TYPE_1__* bclk_ratios ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* lrclk_ratios ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8523_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8523_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);
	int i;
	u16 aifctrl1 = snd_soc_component_read32(component, WM8523_AIF_CTRL1);
	u16 aifctrl2 = snd_soc_component_read32(component, WM8523_AIF_CTRL2);

	/* Find a supported LRCLK ratio */
	for (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) {
		if (wm8523->sysclk / params_rate(params) ==
		    lrclk_ratios[i].ratio)
			break;
	}

	/* Should never happen, should be handled by constraints */
	if (i == ARRAY_SIZE(lrclk_ratios)) {
		dev_err(component->dev, "MCLK/fs ratio %d unsupported\n",
			wm8523->sysclk / params_rate(params));
		return -EINVAL;
	}

	aifctrl2 &= ~WM8523_SR_MASK;
	aifctrl2 |= lrclk_ratios[i].value;

	if (aifctrl1 & WM8523_AIF_MSTR) {
		/* Find a fs->bclk ratio */
		for (i = 0; i < ARRAY_SIZE(bclk_ratios); i++)
			if (params_width(params) * 2 <= bclk_ratios[i].ratio)
				break;

		if (i == ARRAY_SIZE(bclk_ratios)) {
			dev_err(component->dev,
				"No matching BCLK/fs ratio for word length %d\n",
				params_width(params));
			return -EINVAL;
		}

		aifctrl2 &= ~WM8523_BCLKDIV_MASK;
		aifctrl2 |= bclk_ratios[i].value << WM8523_BCLKDIV_SHIFT;
	}

	aifctrl1 &= ~WM8523_WL_MASK;
	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		aifctrl1 |= 0x8;
		break;
	case 24:
		aifctrl1 |= 0x10;
		break;
	case 32:
		aifctrl1 |= 0x18;
		break;
	}

	snd_soc_component_write(component, WM8523_AIF_CTRL1, aifctrl1);
	snd_soc_component_write(component, WM8523_AIF_CTRL2, aifctrl2);

	return 0;
}