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
struct wm8770_priv {int sysclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 int /*<<< orphan*/  WM8770_IFACECTRL ; 
 int /*<<< orphan*/  WM8770_MSTRCTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int* mclk_ratios ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8770_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8770_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component;
	struct wm8770_priv *wm8770;
	int i;
	int iface;
	int shift;
	int ratio;

	component = dai->component;
	wm8770 = snd_soc_component_get_drvdata(component);

	iface = 0;
	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		iface |= 0x10;
		break;
	case 24:
		iface |= 0x20;
		break;
	case 32:
		iface |= 0x30;
		break;
	}

	switch (substream->stream) {
	case SNDRV_PCM_STREAM_PLAYBACK:
		i = 0;
		shift = 4;
		break;
	case SNDRV_PCM_STREAM_CAPTURE:
		i = 2;
		shift = 0;
		break;
	default:
		return -EINVAL;
	}

	/* Only need to set MCLK/LRCLK ratio if we're master */
	if (snd_soc_component_read32(component, WM8770_MSTRCTRL) & 0x100) {
		for (; i < ARRAY_SIZE(mclk_ratios); ++i) {
			ratio = wm8770->sysclk / params_rate(params);
			if (ratio == mclk_ratios[i])
				break;
		}

		if (i == ARRAY_SIZE(mclk_ratios)) {
			dev_err(component->dev,
				"Unable to configure MCLK ratio %d/%d\n",
				wm8770->sysclk, params_rate(params));
			return -EINVAL;
		}

		dev_dbg(component->dev, "MCLK is %dfs\n", mclk_ratios[i]);

		snd_soc_component_update_bits(component, WM8770_MSTRCTRL, 0x7 << shift,
				    i << shift);
	}

	snd_soc_component_update_bits(component, WM8770_IFACECTRL, 0x30, iface);

	return 0;
}