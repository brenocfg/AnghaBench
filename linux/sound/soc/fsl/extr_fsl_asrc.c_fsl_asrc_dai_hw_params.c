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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct fsl_asrc_pair* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct fsl_asrc_pair {int /*<<< orphan*/  index; struct asrc_config* config; } ;
struct fsl_asrc {int asrc_width; unsigned int asrc_rate; } ;
struct asrc_config {unsigned int channel_num; int input_word_width; int output_word_width; unsigned int input_sample_rate; unsigned int output_sample_rate; int /*<<< orphan*/  outclk; int /*<<< orphan*/  inclk; int /*<<< orphan*/  pair; } ;

/* Variables and functions */
 int ASRC_WIDTH_16_BIT ; 
 int ASRC_WIDTH_24_BIT ; 
 int /*<<< orphan*/  INCLK_NONE ; 
 int /*<<< orphan*/  OUTCLK_ASRCK1_CLK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fsl_asrc_config_pair (struct fsl_asrc_pair*) ; 
 int fsl_asrc_request_pair (unsigned int,struct fsl_asrc_pair*) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct fsl_asrc* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_asrc_dai_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct fsl_asrc *asrc_priv = snd_soc_dai_get_drvdata(dai);
	int width = params_width(params);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct fsl_asrc_pair *pair = runtime->private_data;
	unsigned int channels = params_channels(params);
	unsigned int rate = params_rate(params);
	struct asrc_config config;
	int word_width, ret;

	ret = fsl_asrc_request_pair(channels, pair);
	if (ret) {
		dev_err(dai->dev, "fail to request asrc pair\n");
		return ret;
	}

	pair->config = &config;

	if (width == 16)
		width = ASRC_WIDTH_16_BIT;
	else
		width = ASRC_WIDTH_24_BIT;

	if (asrc_priv->asrc_width == 16)
		word_width = ASRC_WIDTH_16_BIT;
	else
		word_width = ASRC_WIDTH_24_BIT;

	config.pair = pair->index;
	config.channel_num = channels;
	config.inclk = INCLK_NONE;
	config.outclk = OUTCLK_ASRCK1_CLK;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		config.input_word_width   = width;
		config.output_word_width  = word_width;
		config.input_sample_rate  = rate;
		config.output_sample_rate = asrc_priv->asrc_rate;
	} else {
		config.input_word_width   = word_width;
		config.output_word_width  = width;
		config.input_sample_rate  = asrc_priv->asrc_rate;
		config.output_sample_rate = rate;
	}

	ret = fsl_asrc_config_pair(pair);
	if (ret) {
		dev_err(dai->dev, "fail to config asrc pair\n");
		return ret;
	}

	return 0;
}