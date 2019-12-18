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
typedef  int u16 ;
struct wm8737_priv {int mclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {scalar_t__ rate; int mclk; int usb; int sr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WM8737_AUDIO_FORMAT ; 
 int WM8737_CLKDIV2 ; 
 int /*<<< orphan*/  WM8737_CLOCKING ; 
 int WM8737_SR_MASK ; 
 int WM8737_SR_SHIFT ; 
 int WM8737_USB_MODE ; 
 int WM8737_WL_MASK ; 
 TYPE_1__* coeff_div ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8737_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8737_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8737_priv *wm8737 = snd_soc_component_get_drvdata(component);
	int i;
	u16 clocking = 0;
	u16 af = 0;

	for (i = 0; i < ARRAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].rate != params_rate(params))
			continue;

		if (coeff_div[i].mclk == wm8737->mclk)
			break;

		if (coeff_div[i].mclk == wm8737->mclk * 2) {
			clocking |= WM8737_CLKDIV2;
			break;
		}
	}

	if (i == ARRAY_SIZE(coeff_div)) {
		dev_err(component->dev, "%dHz MCLK can't support %dHz\n",
			wm8737->mclk, params_rate(params));
		return -EINVAL;
	}

	clocking |= coeff_div[i].usb | (coeff_div[i].sr << WM8737_SR_SHIFT);

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		af |= 0x8;
		break;
	case 24:
		af |= 0x10;
		break;
	case 32:
		af |= 0x18;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, WM8737_AUDIO_FORMAT, WM8737_WL_MASK, af);
	snd_soc_component_update_bits(component, WM8737_CLOCKING,
			    WM8737_USB_MODE | WM8737_CLKDIV2 | WM8737_SR_MASK,
			    clocking);

	return 0;
}