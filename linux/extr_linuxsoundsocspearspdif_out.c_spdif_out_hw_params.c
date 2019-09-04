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
typedef  int u32 ;
struct TYPE_2__ {int core_freq; int rate; } ;
struct spdif_out_dev {TYPE_1__ saved_params; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct spdif_out_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spdif_out_clock (struct spdif_out_dev*,int,int) ; 

__attribute__((used)) static int spdif_out_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	struct spdif_out_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 rate, core_freq;

	if (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		return -EINVAL;

	rate = params_rate(params);

	switch (rate) {
	case 8000:
	case 16000:
	case 32000:
	case 64000:
		/*
		 * The clock is multiplied by 10 to bring it to feasible range
		 * of frequencies for sscg
		 */
		core_freq = 64000 * 128 * 10;	/* 81.92 MHz */
		break;
	case 5512:
	case 11025:
	case 22050:
	case 44100:
	case 88200:
	case 176400:
		core_freq = 176400 * 128;	/* 22.5792 MHz */
		break;
	case 48000:
	case 96000:
	case 192000:
	default:
		core_freq = 192000 * 128;	/* 24.576 MHz */
		break;
	}

	spdif_out_clock(host, core_freq, rate);
	host->saved_params.core_freq = core_freq;
	host->saved_params.rate = rate;

	return 0;
}