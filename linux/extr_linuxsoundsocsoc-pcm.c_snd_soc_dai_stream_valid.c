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
struct snd_soc_pcm_stream {int rates; } ;
struct snd_soc_dai {TYPE_1__* driver; } ;
struct TYPE_2__ {struct snd_soc_pcm_stream capture; struct snd_soc_pcm_stream playback; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static bool snd_soc_dai_stream_valid(struct snd_soc_dai *dai, int stream)
{
	struct snd_soc_pcm_stream *codec_stream;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		codec_stream = &dai->driver->playback;
	else
		codec_stream = &dai->driver->capture;

	/* If the codec specifies any rate at all, it supports the stream. */
	return codec_stream->rates;
}