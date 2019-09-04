#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct snd_soc_pcm_stream {unsigned int channels_min; unsigned int channels_max; unsigned int rate_min; unsigned int rate_max; int formats; unsigned int rates; } ;
struct snd_soc_pcm_runtime {int num_codecs; TYPE_2__** codec_dais; TYPE_1__* cpu_dai; } ;
struct snd_soc_dai_driver {struct snd_soc_pcm_stream capture; struct snd_soc_pcm_stream playback; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_hardware {int formats; unsigned int rate_min; unsigned int rate_max; void* rates; void* channels_max; void* channels_min; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct TYPE_4__ {struct snd_soc_dai_driver* driver; } ;
struct TYPE_3__ {struct snd_soc_dai_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned int UINT_MAX ; 
 int ULLONG_MAX ; 
 void* max (unsigned int,unsigned int) ; 
 void* min (unsigned int,unsigned int) ; 
 void* min_not_zero (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 void* snd_pcm_rate_mask_intersect (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_dai_stream_valid (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soc_pcm_init_runtime_hw(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hardware *hw = &runtime->hw;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai_driver *cpu_dai_drv = rtd->cpu_dai->driver;
	struct snd_soc_dai_driver *codec_dai_drv;
	struct snd_soc_pcm_stream *codec_stream;
	struct snd_soc_pcm_stream *cpu_stream;
	unsigned int chan_min = 0, chan_max = UINT_MAX;
	unsigned int rate_min = 0, rate_max = UINT_MAX;
	unsigned int rates = UINT_MAX;
	u64 formats = ULLONG_MAX;
	int i;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cpu_stream = &cpu_dai_drv->playback;
	else
		cpu_stream = &cpu_dai_drv->capture;

	/* first calculate min/max only for CODECs in the DAI link */
	for (i = 0; i < rtd->num_codecs; i++) {

		/*
		 * Skip CODECs which don't support the current stream type.
		 * Otherwise, since the rate, channel, and format values will
		 * zero in that case, we would have no usable settings left,
		 * causing the resulting setup to fail.
		 * At least one CODEC should match, otherwise we should have
		 * bailed out on a higher level, since there would be no
		 * CODEC to support the transfer direction in that case.
		 */
		if (!snd_soc_dai_stream_valid(rtd->codec_dais[i],
					      substream->stream))
			continue;

		codec_dai_drv = rtd->codec_dais[i]->driver;
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			codec_stream = &codec_dai_drv->playback;
		else
			codec_stream = &codec_dai_drv->capture;
		chan_min = max(chan_min, codec_stream->channels_min);
		chan_max = min(chan_max, codec_stream->channels_max);
		rate_min = max(rate_min, codec_stream->rate_min);
		rate_max = min_not_zero(rate_max, codec_stream->rate_max);
		formats &= codec_stream->formats;
		rates = snd_pcm_rate_mask_intersect(codec_stream->rates, rates);
	}

	/*
	 * chan min/max cannot be enforced if there are multiple CODEC DAIs
	 * connected to a single CPU DAI, use CPU DAI's directly and let
	 * channel allocation be fixed up later
	 */
	if (rtd->num_codecs > 1) {
		chan_min = cpu_stream->channels_min;
		chan_max = cpu_stream->channels_max;
	}

	hw->channels_min = max(chan_min, cpu_stream->channels_min);
	hw->channels_max = min(chan_max, cpu_stream->channels_max);
	if (hw->formats)
		hw->formats &= formats & cpu_stream->formats;
	else
		hw->formats = formats & cpu_stream->formats;
	hw->rates = snd_pcm_rate_mask_intersect(rates, cpu_stream->rates);

	snd_pcm_limit_hw_rates(runtime);

	hw->rate_min = max(hw->rate_min, cpu_stream->rate_min);
	hw->rate_min = max(hw->rate_min, rate_min);
	hw->rate_max = min_not_zero(hw->rate_max, cpu_stream->rate_max);
	hw->rate_max = min_not_zero(hw->rate_max, rate_max);
}