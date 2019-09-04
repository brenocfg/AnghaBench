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
struct wm8961_priv {int sysclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int val; int ratio; scalar_t__ rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  WM8961_ADC_DAC_CONTROL_2 ; 
 int /*<<< orphan*/  WM8961_ADDITIONAL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8961_AUDIO_INTERFACE_0 ; 
 int WM8961_CLK_SYS_RATE_MASK ; 
 int WM8961_CLK_SYS_RATE_SHIFT ; 
 int /*<<< orphan*/  WM8961_CLOCKING_4 ; 
 int WM8961_DACSLOPE ; 
 int WM8961_SAMPLE_RATE_MASK ; 
 int WM8961_WL_MASK ; 
 int WM8961_WL_SHIFT ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8961_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* wm8961_clk_sys_ratio ; 
 TYPE_1__* wm8961_srate ; 

__attribute__((used)) static int wm8961_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8961_priv *wm8961 = snd_soc_component_get_drvdata(component);
	int i, best, target, fs;
	u16 reg;

	fs = params_rate(params);

	if (!wm8961->sysclk) {
		dev_err(component->dev, "MCLK has not been specified\n");
		return -EINVAL;
	}

	/* Find the closest sample rate for the filters */
	best = 0;
	for (i = 0; i < ARRAY_SIZE(wm8961_srate); i++) {
		if (abs(wm8961_srate[i].rate - fs) <
		    abs(wm8961_srate[best].rate - fs))
			best = i;
	}
	reg = snd_soc_component_read32(component, WM8961_ADDITIONAL_CONTROL_3);
	reg &= ~WM8961_SAMPLE_RATE_MASK;
	reg |= wm8961_srate[best].val;
	snd_soc_component_write(component, WM8961_ADDITIONAL_CONTROL_3, reg);
	dev_dbg(component->dev, "Selected SRATE %dHz for %dHz\n",
		wm8961_srate[best].rate, fs);

	/* Select a CLK_SYS/fs ratio equal to or higher than required */
	target = wm8961->sysclk / fs;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK && target < 64) {
		dev_err(component->dev,
			"SYSCLK must be at least 64*fs for DAC\n");
		return -EINVAL;
	}
	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE && target < 256) {
		dev_err(component->dev,
			"SYSCLK must be at least 256*fs for ADC\n");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(wm8961_clk_sys_ratio); i++) {
		if (wm8961_clk_sys_ratio[i].ratio >= target)
			break;
	}
	if (i == ARRAY_SIZE(wm8961_clk_sys_ratio)) {
		dev_err(component->dev, "Unable to generate CLK_SYS_RATE\n");
		return -EINVAL;
	}
	dev_dbg(component->dev, "Selected CLK_SYS_RATE of %d for %d/%d=%d\n",
		wm8961_clk_sys_ratio[i].ratio, wm8961->sysclk, fs,
		wm8961->sysclk / fs);

	reg = snd_soc_component_read32(component, WM8961_CLOCKING_4);
	reg &= ~WM8961_CLK_SYS_RATE_MASK;
	reg |= wm8961_clk_sys_ratio[i].val << WM8961_CLK_SYS_RATE_SHIFT;
	snd_soc_component_write(component, WM8961_CLOCKING_4, reg);

	reg = snd_soc_component_read32(component, WM8961_AUDIO_INTERFACE_0);
	reg &= ~WM8961_WL_MASK;
	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		reg |= 1 << WM8961_WL_SHIFT;
		break;
	case 24:
		reg |= 2 << WM8961_WL_SHIFT;
		break;
	case 32:
		reg |= 3 << WM8961_WL_SHIFT;
		break;
	default:
		return -EINVAL;
	}
	snd_soc_component_write(component, WM8961_AUDIO_INTERFACE_0, reg);

	/* Sloping stop-band filter is recommended for <= 24kHz */
	reg = snd_soc_component_read32(component, WM8961_ADC_DAC_CONTROL_2);
	if (fs <= 24000)
		reg |= WM8961_DACSLOPE;
	else
		reg &= ~WM8961_DACSLOPE;
	snd_soc_component_write(component, WM8961_ADC_DAC_CONTROL_2, reg);

	return 0;
}