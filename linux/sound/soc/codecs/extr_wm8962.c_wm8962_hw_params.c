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
struct wm8962_priv {int bclk; int lrclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {int rate; int reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ SND_SOC_BIAS_ON ; 
 int /*<<< orphan*/  WM8962_ADDITIONAL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8962_AUDIO_INTERFACE_0 ; 
 int WM8962_SAMPLE_RATE_INT_MODE ; 
 int WM8962_SAMPLE_RATE_MASK ; 
 int WM8962_WL_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 scalar_t__ snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8962_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 
 TYPE_1__* sr_vals ; 
 int /*<<< orphan*/  wm8962_configure_bclk (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8962_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8962_priv *wm8962 = snd_soc_component_get_drvdata(component);
	int i;
	int aif0 = 0;
	int adctl3 = 0;

	wm8962->bclk = snd_soc_params_to_bclk(params);
	if (params_channels(params) == 1)
		wm8962->bclk *= 2;

	wm8962->lrclk = params_rate(params);

	for (i = 0; i < ARRAY_SIZE(sr_vals); i++) {
		if (sr_vals[i].rate == wm8962->lrclk) {
			adctl3 |= sr_vals[i].reg;
			break;
		}
	}
	if (i == ARRAY_SIZE(sr_vals)) {
		dev_err(component->dev, "Unsupported rate %dHz\n", wm8962->lrclk);
		return -EINVAL;
	}

	if (wm8962->lrclk % 8000 == 0)
		adctl3 |= WM8962_SAMPLE_RATE_INT_MODE;

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		aif0 |= 0x4;
		break;
	case 24:
		aif0 |= 0x8;
		break;
	case 32:
		aif0 |= 0xc;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, WM8962_AUDIO_INTERFACE_0,
			    WM8962_WL_MASK, aif0);
	snd_soc_component_update_bits(component, WM8962_ADDITIONAL_CONTROL_3,
			    WM8962_SAMPLE_RATE_INT_MODE |
			    WM8962_SAMPLE_RATE_MASK, adctl3);

	dev_dbg(component->dev, "hw_params set BCLK %dHz LRCLK %dHz\n",
		wm8962->bclk, wm8962->lrclk);

	if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON)
		wm8962_configure_bclk(component);

	return 0;
}