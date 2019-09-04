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
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
struct kirkwood_dma_data {scalar_t__ io; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ KIRKWOOD_PLAY_BYTE_COUNT ; 
 scalar_t__ KIRKWOOD_REC_BYTE_COUNT ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kirkwood_dma_data* kirkwood_priv (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static snd_pcm_uframes_t kirkwood_dma_pointer(struct snd_pcm_substream
						*substream)
{
	struct kirkwood_dma_data *priv = kirkwood_priv(substream);
	snd_pcm_uframes_t count;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		count = bytes_to_frames(substream->runtime,
			readl(priv->io + KIRKWOOD_PLAY_BYTE_COUNT));
	else
		count = bytes_to_frames(substream->runtime,
			readl(priv->io + KIRKWOOD_REC_BYTE_COUNT));

	return count;
}