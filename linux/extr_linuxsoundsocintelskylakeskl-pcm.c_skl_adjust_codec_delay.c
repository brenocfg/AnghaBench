#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long long u64 ;
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {TYPE_2__* driver; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct TYPE_6__ {long long (* delay ) (struct snd_pcm_substream*,struct snd_soc_dai*) ;} ;
struct TYPE_5__ {TYPE_3__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 long long div_u64 (long long,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 long long stub1 (struct snd_pcm_substream*,struct snd_soc_dai*) ; 

__attribute__((used)) static u64 skl_adjust_codec_delay(struct snd_pcm_substream *substream,
				u64 nsec)
{
	struct snd_soc_pcm_runtime *rtd = snd_pcm_substream_chip(substream);
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	u64 codec_frames, codec_nsecs;

	if (!codec_dai->driver->ops->delay)
		return nsec;

	codec_frames = codec_dai->driver->ops->delay(substream, codec_dai);
	codec_nsecs = div_u64(codec_frames * 1000000000LL,
			      substream->runtime->rate);

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		return nsec + codec_nsecs;

	return (nsec > codec_nsecs) ? nsec - codec_nsecs : 0;
}