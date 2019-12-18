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
struct wm2200_priv {int sysclk; scalar_t__ symmetric_rates; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int WM2200_AIF1RX_BCPF_MASK ; 
 int WM2200_AIF1RX_SLOT_LEN_MASK ; 
 int WM2200_AIF1RX_WL_MASK ; 
 int WM2200_AIF1TX_BCPF_MASK ; 
 int WM2200_AIF1TX_SLOT_LEN_MASK ; 
 int WM2200_AIF1TX_WL_MASK ; 
 int WM2200_AIF1TX_WL_SHIFT ; 
 int WM2200_AIF1_BCLK_DIV_MASK ; 
 int /*<<< orphan*/  WM2200_AUDIO_IF_1_1 ; 
 int /*<<< orphan*/  WM2200_AUDIO_IF_1_6 ; 
 int /*<<< orphan*/  WM2200_AUDIO_IF_1_7 ; 
 int /*<<< orphan*/  WM2200_AUDIO_IF_1_8 ; 
 int /*<<< orphan*/  WM2200_AUDIO_IF_1_9 ; 
 int /*<<< orphan*/  WM2200_CLOCKING_4 ; 
 int WM2200_NUM_BCLK_RATES ; 
 int WM2200_SAMPLE_RATE_1_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm2200_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 
 int* wm2200_bclk_rates_cd ; 
 int* wm2200_bclk_rates_dat ; 
 int* wm2200_sr_code ; 

__attribute__((used)) static int wm2200_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	int i, bclk, lrclk, wl, fl, sr_code;
	int *bclk_rates;

	/* Data sizes if not using TDM */
	wl = params_width(params);
	if (wl < 0)
		return wl;
	fl = snd_soc_params_to_frame_size(params);
	if (fl < 0)
		return fl;

	dev_dbg(component->dev, "Word length %d bits, frame length %d bits\n",
		wl, fl);

	/* Target BCLK rate */
	bclk = snd_soc_params_to_bclk(params);
	if (bclk < 0)
		return bclk;

	if (!wm2200->sysclk) {
		dev_err(component->dev, "SYSCLK has no rate set\n");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(wm2200_sr_code); i++)
		if (wm2200_sr_code[i] == params_rate(params))
			break;
	if (i == ARRAY_SIZE(wm2200_sr_code)) {
		dev_err(component->dev, "Unsupported sample rate: %dHz\n",
			params_rate(params));
		return -EINVAL;
	}
	sr_code = i;

	dev_dbg(component->dev, "Target BCLK is %dHz, using %dHz SYSCLK\n",
		bclk, wm2200->sysclk);

	if (wm2200->sysclk % 4000)
		bclk_rates = wm2200_bclk_rates_cd;
	else
		bclk_rates = wm2200_bclk_rates_dat;

	for (i = 0; i < WM2200_NUM_BCLK_RATES; i++)
		if (bclk_rates[i] >= bclk && (bclk_rates[i] % bclk == 0))
			break;
	if (i == WM2200_NUM_BCLK_RATES) {
		dev_err(component->dev,
			"No valid BCLK for %dHz found from %dHz SYSCLK\n",
			bclk, wm2200->sysclk);
		return -EINVAL;
	}

	bclk = i;
	dev_dbg(component->dev, "Setting %dHz BCLK\n", bclk_rates[bclk]);
	snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_1,
			    WM2200_AIF1_BCLK_DIV_MASK, bclk);

	lrclk = bclk_rates[bclk] / params_rate(params);
	dev_dbg(component->dev, "Setting %dHz LRCLK\n", bclk_rates[bclk] / lrclk);
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
	    wm2200->symmetric_rates)
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_7,
				    WM2200_AIF1RX_BCPF_MASK, lrclk);
	else
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_6,
				    WM2200_AIF1TX_BCPF_MASK, lrclk);

	i = (wl << WM2200_AIF1TX_WL_SHIFT) | wl;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_9,
				    WM2200_AIF1RX_WL_MASK |
				    WM2200_AIF1RX_SLOT_LEN_MASK, i);
	else
		snd_soc_component_update_bits(component, WM2200_AUDIO_IF_1_8,
				    WM2200_AIF1TX_WL_MASK |
				    WM2200_AIF1TX_SLOT_LEN_MASK, i);

	snd_soc_component_update_bits(component, WM2200_CLOCKING_4,
			    WM2200_SAMPLE_RATE_1_MASK, sr_code);

	return 0;
}