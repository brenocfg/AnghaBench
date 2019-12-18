#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8903_priv {int sysclk; void* fs; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_5__ {int rate; int value; int mclk_div; int div; int mode; int ratio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int WM8903_AIF_WL_MASK ; 
 int /*<<< orphan*/  WM8903_AUDIO_INTERFACE_1 ; 
 int /*<<< orphan*/  WM8903_AUDIO_INTERFACE_2 ; 
 int /*<<< orphan*/  WM8903_AUDIO_INTERFACE_3 ; 
 int WM8903_BCLK_DIV_MASK ; 
 int WM8903_CLK_SYS_MODE_MASK ; 
 int WM8903_CLK_SYS_MODE_SHIFT ; 
 int WM8903_CLK_SYS_RATE_MASK ; 
 int WM8903_CLK_SYS_RATE_SHIFT ; 
 int /*<<< orphan*/  WM8903_CLOCK_RATES_0 ; 
 int /*<<< orphan*/  WM8903_CLOCK_RATES_1 ; 
 int /*<<< orphan*/  WM8903_DAC_DIGITAL_1 ; 
 int WM8903_DAC_SB_FILT ; 
 int WM8903_LRCLK_RATE_MASK ; 
 int WM8903_MCLKDIV2 ; 
 int WM8903_SAMPLE_RATE_MASK ; 
 int abs (int) ; 
 TYPE_1__* bclk_divs ; 
 TYPE_1__* clk_sys_ratios ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 void* params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 TYPE_1__* sample_rates ; 
 struct wm8903_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8903_set_deemph (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8903_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8903_priv *wm8903 = snd_soc_component_get_drvdata(component);
	int fs = params_rate(params);
	int bclk;
	int bclk_div;
	int i;
	int dsp_config;
	int clk_config;
	int best_val;
	int cur_val;
	int clk_sys;

	u16 aif1 = snd_soc_component_read32(component, WM8903_AUDIO_INTERFACE_1);
	u16 aif2 = snd_soc_component_read32(component, WM8903_AUDIO_INTERFACE_2);
	u16 aif3 = snd_soc_component_read32(component, WM8903_AUDIO_INTERFACE_3);
	u16 clock0 = snd_soc_component_read32(component, WM8903_CLOCK_RATES_0);
	u16 clock1 = snd_soc_component_read32(component, WM8903_CLOCK_RATES_1);
	u16 dac_digital1 = snd_soc_component_read32(component, WM8903_DAC_DIGITAL_1);

	/* Enable sloping stopband filter for low sample rates */
	if (fs <= 24000)
		dac_digital1 |= WM8903_DAC_SB_FILT;
	else
		dac_digital1 &= ~WM8903_DAC_SB_FILT;

	/* Configure sample rate logic for DSP - choose nearest rate */
	dsp_config = 0;
	best_val = abs(sample_rates[dsp_config].rate - fs);
	for (i = 1; i < ARRAY_SIZE(sample_rates); i++) {
		cur_val = abs(sample_rates[i].rate - fs);
		if (cur_val <= best_val) {
			dsp_config = i;
			best_val = cur_val;
		}
	}

	dev_dbg(component->dev, "DSP fs = %dHz\n", sample_rates[dsp_config].rate);
	clock1 &= ~WM8903_SAMPLE_RATE_MASK;
	clock1 |= sample_rates[dsp_config].value;

	aif1 &= ~WM8903_AIF_WL_MASK;
	bclk = 2 * fs;
	switch (params_width(params)) {
	case 16:
		bclk *= 16;
		break;
	case 20:
		bclk *= 20;
		aif1 |= 0x4;
		break;
	case 24:
		bclk *= 24;
		aif1 |= 0x8;
		break;
	case 32:
		bclk *= 32;
		aif1 |= 0xc;
		break;
	default:
		return -EINVAL;
	}

	dev_dbg(component->dev, "MCLK = %dHz, target sample rate = %dHz\n",
		wm8903->sysclk, fs);

	/* We may not have an MCLK which allows us to generate exactly
	 * the clock we want, particularly with USB derived inputs, so
	 * approximate.
	 */
	clk_config = 0;
	best_val = abs((wm8903->sysclk /
			(clk_sys_ratios[0].mclk_div *
			 clk_sys_ratios[0].div)) - fs);
	for (i = 1; i < ARRAY_SIZE(clk_sys_ratios); i++) {
		cur_val = abs((wm8903->sysclk /
			       (clk_sys_ratios[i].mclk_div *
				clk_sys_ratios[i].div)) - fs);

		if (cur_val <= best_val) {
			clk_config = i;
			best_val = cur_val;
		}
	}

	if (clk_sys_ratios[clk_config].mclk_div == 2) {
		clock0 |= WM8903_MCLKDIV2;
		clk_sys = wm8903->sysclk / 2;
	} else {
		clock0 &= ~WM8903_MCLKDIV2;
		clk_sys = wm8903->sysclk;
	}

	clock1 &= ~(WM8903_CLK_SYS_RATE_MASK |
		    WM8903_CLK_SYS_MODE_MASK);
	clock1 |= clk_sys_ratios[clk_config].rate << WM8903_CLK_SYS_RATE_SHIFT;
	clock1 |= clk_sys_ratios[clk_config].mode << WM8903_CLK_SYS_MODE_SHIFT;

	dev_dbg(component->dev, "CLK_SYS_RATE=%x, CLK_SYS_MODE=%x div=%d\n",
		clk_sys_ratios[clk_config].rate,
		clk_sys_ratios[clk_config].mode,
		clk_sys_ratios[clk_config].div);

	dev_dbg(component->dev, "Actual CLK_SYS = %dHz\n", clk_sys);

	/* We may not get quite the right frequency if using
	 * approximate clocks so look for the closest match that is
	 * higher than the target (we need to ensure that there enough
	 * BCLKs to clock out the samples).
	 */
	bclk_div = 0;
	best_val = ((clk_sys * 10) / bclk_divs[0].ratio) - bclk;
	i = 1;
	while (i < ARRAY_SIZE(bclk_divs)) {
		cur_val = ((clk_sys * 10) / bclk_divs[i].ratio) - bclk;
		if (cur_val < 0) /* BCLK table is sorted */
			break;
		bclk_div = i;
		best_val = cur_val;
		i++;
	}

	aif2 &= ~WM8903_BCLK_DIV_MASK;
	aif3 &= ~WM8903_LRCLK_RATE_MASK;

	dev_dbg(component->dev, "BCLK ratio %d for %dHz - actual BCLK = %dHz\n",
		bclk_divs[bclk_div].ratio / 10, bclk,
		(clk_sys * 10) / bclk_divs[bclk_div].ratio);

	aif2 |= bclk_divs[bclk_div].div;
	aif3 |= bclk / fs;

	wm8903->fs = params_rate(params);
	wm8903_set_deemph(component);

	snd_soc_component_write(component, WM8903_CLOCK_RATES_0, clock0);
	snd_soc_component_write(component, WM8903_CLOCK_RATES_1, clock1);
	snd_soc_component_write(component, WM8903_AUDIO_INTERFACE_1, aif1);
	snd_soc_component_write(component, WM8903_AUDIO_INTERFACE_2, aif2);
	snd_soc_component_write(component, WM8903_AUDIO_INTERFACE_3, aif3);
	snd_soc_component_write(component, WM8903_DAC_DIGITAL_1, dac_digital1);

	return 0;
}