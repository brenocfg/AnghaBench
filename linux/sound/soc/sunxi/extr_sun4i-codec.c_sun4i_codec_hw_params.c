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
struct sun4i_codec {int /*<<< orphan*/  clk_module; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct sun4i_codec* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int sun4i_codec_get_hw_rate (struct snd_pcm_hw_params*) ; 
 unsigned long sun4i_codec_get_mod_freq (struct snd_pcm_hw_params*) ; 
 int sun4i_codec_hw_params_capture (struct sun4i_codec*,struct snd_pcm_hw_params*,int) ; 
 int sun4i_codec_hw_params_playback (struct sun4i_codec*,struct snd_pcm_hw_params*,int) ; 

__attribute__((used)) static int sun4i_codec_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);
	unsigned long clk_freq;
	int ret, hwrate;

	clk_freq = sun4i_codec_get_mod_freq(params);
	if (!clk_freq)
		return -EINVAL;

	ret = clk_set_rate(scodec->clk_module, clk_freq);
	if (ret)
		return ret;

	hwrate = sun4i_codec_get_hw_rate(params);
	if (hwrate < 0)
		return hwrate;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return sun4i_codec_hw_params_playback(scodec, params,
						      hwrate);

	return sun4i_codec_hw_params_capture(scodec, params,
					     hwrate);
}