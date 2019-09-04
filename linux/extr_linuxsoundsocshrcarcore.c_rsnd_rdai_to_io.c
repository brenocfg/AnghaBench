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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {struct rsnd_dai_stream capture; struct rsnd_dai_stream playback; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static
struct rsnd_dai_stream *rsnd_rdai_to_io(struct rsnd_dai *rdai,
					struct snd_pcm_substream *substream)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return &rdai->playback;
	else
		return &rdai->capture;
}