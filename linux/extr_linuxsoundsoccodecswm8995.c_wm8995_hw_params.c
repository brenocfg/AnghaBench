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
struct wm8995_priv {int* aifclk; } ;
struct snd_soc_dai {int id; int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int WM8995_AIF1ADC_LRCLK ; 
 int WM8995_AIF1CLK_RATE_MASK ; 
 int WM8995_AIF1DAC_LRCLK ; 
 int WM8995_AIF1DAC_RATE_MASK ; 
 int WM8995_AIF1_BCLK ; 
 int WM8995_AIF1_BCLK_DIV_MASK ; 
 int WM8995_AIF1_BCLK_DIV_SHIFT ; 
 int WM8995_AIF1_CONTROL_1 ; 
 int WM8995_AIF1_RATE ; 
 int WM8995_AIF1_SR_MASK ; 
 int WM8995_AIF1_SR_SHIFT ; 
 int WM8995_AIF1_WL_MASK ; 
 int WM8995_AIF1_WL_SHIFT ; 
 int WM8995_AIF2ADC_LRCLK ; 
 int WM8995_AIF2DAC_LRCLK ; 
 int WM8995_AIF2_BCLK ; 
 int WM8995_AIF2_CONTROL_1 ; 
 int WM8995_AIF2_RATE ; 
 int abs (int) ; 
 int* bclk_divs ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int* fs_ratios ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8995_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 
 int* srs ; 

__attribute__((used)) static int wm8995_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component;
	struct wm8995_priv *wm8995;
	int aif1_reg;
	int bclk_reg;
	int lrclk_reg;
	int rate_reg;
	int bclk_rate;
	int aif1;
	int lrclk, bclk;
	int i, rate_val, best, best_val, cur_val;

	component = dai->component;
	wm8995 = snd_soc_component_get_drvdata(component);

	switch (dai->id) {
	case 0:
		aif1_reg = WM8995_AIF1_CONTROL_1;
		bclk_reg = WM8995_AIF1_BCLK;
		rate_reg = WM8995_AIF1_RATE;
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK /* ||
			wm8995->lrclk_shared[0] */) {
			lrclk_reg = WM8995_AIF1DAC_LRCLK;
		} else {
			lrclk_reg = WM8995_AIF1ADC_LRCLK;
			dev_dbg(component->dev, "AIF1 using split LRCLK\n");
		}
		break;
	case 1:
		aif1_reg = WM8995_AIF2_CONTROL_1;
		bclk_reg = WM8995_AIF2_BCLK;
		rate_reg = WM8995_AIF2_RATE;
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK /* ||
		    wm8995->lrclk_shared[1] */) {
			lrclk_reg = WM8995_AIF2DAC_LRCLK;
		} else {
			lrclk_reg = WM8995_AIF2ADC_LRCLK;
			dev_dbg(component->dev, "AIF2 using split LRCLK\n");
		}
		break;
	default:
		return -EINVAL;
	}

	bclk_rate = snd_soc_params_to_bclk(params);
	if (bclk_rate < 0)
		return bclk_rate;

	aif1 = 0;
	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		aif1 |= (0x1 << WM8995_AIF1_WL_SHIFT);
		break;
	case 24:
		aif1 |= (0x2 << WM8995_AIF1_WL_SHIFT);
		break;
	case 32:
		aif1 |= (0x3 << WM8995_AIF1_WL_SHIFT);
		break;
	default:
		dev_err(dai->dev, "Unsupported word length %u\n",
			params_width(params));
		return -EINVAL;
	}

	/* try to find a suitable sample rate */
	for (i = 0; i < ARRAY_SIZE(srs); ++i)
		if (srs[i] == params_rate(params))
			break;
	if (i == ARRAY_SIZE(srs)) {
		dev_err(dai->dev, "Sample rate %d is not supported\n",
			params_rate(params));
		return -EINVAL;
	}
	rate_val = i << WM8995_AIF1_SR_SHIFT;

	dev_dbg(dai->dev, "Sample rate is %dHz\n", srs[i]);
	dev_dbg(dai->dev, "AIF%dCLK is %dHz, target BCLK %dHz\n",
		dai->id + 1, wm8995->aifclk[dai->id], bclk_rate);

	/* AIFCLK/fs ratio; look for a close match in either direction */
	best = 1;
	best_val = abs((fs_ratios[1] * params_rate(params))
		       - wm8995->aifclk[dai->id]);
	for (i = 2; i < ARRAY_SIZE(fs_ratios); i++) {
		cur_val = abs((fs_ratios[i] * params_rate(params))
			      - wm8995->aifclk[dai->id]);
		if (cur_val >= best_val)
			continue;
		best = i;
		best_val = cur_val;
	}
	rate_val |= best;

	dev_dbg(dai->dev, "Selected AIF%dCLK/fs = %d\n",
		dai->id + 1, fs_ratios[best]);

	/*
	 * We may not get quite the right frequency if using
	 * approximate clocks so look for the closest match that is
	 * higher than the target (we need to ensure that there enough
	 * BCLKs to clock out the samples).
	 */
	best = 0;
	bclk = 0;
	for (i = 0; i < ARRAY_SIZE(bclk_divs); i++) {
		cur_val = (wm8995->aifclk[dai->id] * 10 / bclk_divs[i]) - bclk_rate;
		if (cur_val < 0) /* BCLK table is sorted */
			break;
		best = i;
	}
	bclk |= best << WM8995_AIF1_BCLK_DIV_SHIFT;

	bclk_rate = wm8995->aifclk[dai->id] * 10 / bclk_divs[best];
	dev_dbg(dai->dev, "Using BCLK_DIV %d for actual BCLK %dHz\n",
		bclk_divs[best], bclk_rate);

	lrclk = bclk_rate / params_rate(params);
	dev_dbg(dai->dev, "Using LRCLK rate %d for actual LRCLK %dHz\n",
		lrclk, bclk_rate / lrclk);

	snd_soc_component_update_bits(component, aif1_reg,
			    WM8995_AIF1_WL_MASK, aif1);
	snd_soc_component_update_bits(component, bclk_reg,
			    WM8995_AIF1_BCLK_DIV_MASK, bclk);
	snd_soc_component_update_bits(component, lrclk_reg,
			    WM8995_AIF1DAC_RATE_MASK, lrclk);
	snd_soc_component_update_bits(component, rate_reg,
			    WM8995_AIF1_SR_MASK |
			    WM8995_AIF1CLK_RATE_MASK, rate_val);
	return 0;
}