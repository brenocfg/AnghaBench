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
typedef  int u16 ;
struct wm8580_priv {int* sysclk; } ;
struct snd_soc_dai {TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {size_t id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int WM8580_AIF_BCLKSEL_MASK ; 
 int WM8580_AIF_LENGTH_20 ; 
 int WM8580_AIF_LENGTH_24 ; 
 int WM8580_AIF_LENGTH_32 ; 
 int WM8580_AIF_LENGTH_MASK ; 
 int WM8580_AIF_RATE_MASK ; 
 int WM8580_DACOSR ; 
 scalar_t__ WM8580_PAIF1 ; 
 scalar_t__ WM8580_PAIF3 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8580_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,scalar_t__,int,int) ; 
 int* wm8580_sysclk_ratios ; 

__attribute__((used)) static int wm8580_paif_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);
	u16 paifa = 0;
	u16 paifb = 0;
	int i, ratio, osr;

	/* bit size */
	switch (params_width(params)) {
	case 16:
		paifa |= 0x8;
		break;
	case 20:
		paifa |= 0x0;
		paifb |= WM8580_AIF_LENGTH_20;
		break;
	case 24:
		paifa |= 0x0;
		paifb |= WM8580_AIF_LENGTH_24;
		break;
	case 32:
		paifa |= 0x0;
		paifb |= WM8580_AIF_LENGTH_32;
		break;
	default:
		return -EINVAL;
	}

	/* Look up the SYSCLK ratio; accept only exact matches */
	ratio = wm8580->sysclk[dai->driver->id] / params_rate(params);
	for (i = 0; i < ARRAY_SIZE(wm8580_sysclk_ratios); i++)
		if (ratio == wm8580_sysclk_ratios[i])
			break;
	if (i == ARRAY_SIZE(wm8580_sysclk_ratios)) {
		dev_err(component->dev, "Invalid clock ratio %d/%d\n",
			wm8580->sysclk[dai->driver->id], params_rate(params));
		return -EINVAL;
	}
	paifa |= i;
	dev_dbg(component->dev, "Running at %dfs with %dHz clock\n",
		wm8580_sysclk_ratios[i], wm8580->sysclk[dai->driver->id]);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (ratio) {
		case 128:
		case 192:
			osr = WM8580_DACOSR;
			dev_dbg(component->dev, "Selecting 64x OSR\n");
			break;
		default:
			osr = 0;
			dev_dbg(component->dev, "Selecting 128x OSR\n");
			break;
		}

		snd_soc_component_update_bits(component, WM8580_PAIF3, WM8580_DACOSR, osr);
	}

	snd_soc_component_update_bits(component, WM8580_PAIF1 + dai->driver->id,
			    WM8580_AIF_RATE_MASK | WM8580_AIF_BCLKSEL_MASK,
			    paifa);
	snd_soc_component_update_bits(component, WM8580_PAIF3 + dai->driver->id,
			    WM8580_AIF_LENGTH_MASK, paifb);
	return 0;
}