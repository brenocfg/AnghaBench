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
struct snd_soc_dai {scalar_t__ id; struct snd_soc_component* component; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct device {int dummy; } ;
struct cx2072x_priv {scalar_t__ mclk_rate; int bclk_ratio; int frame_size; int sample_size; unsigned int sample_rate; int en_aec_ref; int pll_changed; int i2spcm_changed; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2072X_ADC1_CONNECTION_SELECT_CONTROL ; 
 scalar_t__ CX2072X_DAI_DSP ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx2072x_config_i2spcm (struct cx2072x_priv*) ; 
 int /*<<< orphan*/  cx2072x_config_pll (struct cx2072x_priv*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int cx2072x_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *codec = dai->component;
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);
	struct device *dev = codec->dev;
	const unsigned int sample_rate = params_rate(params);
	int sample_size, frame_size;

	/* Data sizes if not using TDM */
	sample_size = params_width(params);

	if (sample_size < 0)
		return sample_size;

	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0)
		return frame_size;

	if (cx2072x->mclk_rate == 0) {
		dev_err(dev, "Master clock rate is not configured\n");
		return -EINVAL;
	}

	if (cx2072x->bclk_ratio)
		frame_size = cx2072x->bclk_ratio;

	switch (sample_rate) {
	case 48000:
	case 32000:
	case 24000:
	case 16000:
	case 96000:
	case 192000:
		break;

	default:
		dev_err(dev, "Unsupported sample rate %d\n", sample_rate);
		return -EINVAL;
	}

	dev_dbg(dev, "Sample size %d bits, frame = %d bits, rate = %d Hz\n",
		sample_size, frame_size, sample_rate);

	cx2072x->frame_size = frame_size;
	cx2072x->sample_size = sample_size;
	cx2072x->sample_rate = sample_rate;

	if (dai->id == CX2072X_DAI_DSP) {
		cx2072x->en_aec_ref = true;
		dev_dbg(cx2072x->dev, "enables aec reference\n");
		regmap_write(cx2072x->regmap,
			     CX2072X_ADC1_CONNECTION_SELECT_CONTROL, 3);
	}

	if (cx2072x->pll_changed) {
		cx2072x_config_pll(cx2072x);
		cx2072x->pll_changed = false;
	}

	if (cx2072x->i2spcm_changed) {
		cx2072x_config_i2spcm(cx2072x);
		cx2072x->i2spcm_changed = false;
	}

	return 0;
}