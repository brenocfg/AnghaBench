#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_sgio2audio_chan {int idx; } ;
struct snd_sgio2audio {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct TYPE_8__ {TYPE_2__* chan; } ;
struct TYPE_9__ {TYPE_3__ audio; } ;
struct TYPE_10__ {TYPE_4__ perif; } ;
struct TYPE_7__ {int /*<<< orphan*/  control; } ;
struct TYPE_6__ {struct snd_sgio2audio_chan* private_data; } ;

/* Variables and functions */
 int CHANNEL_CONTROL_RESET ; 
 int CHANNEL_DMA_ENABLE ; 
 int CHANNEL_INT_THRESHOLD_50 ; 
 scalar_t__ CHANNEL_RING_SIZE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_5__* mace ; 
 struct snd_sgio2audio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sgio2audio_dma_push_frag (struct snd_sgio2audio*,int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sgio2audio_dma_start(struct snd_pcm_substream *substream)
{
	struct snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	struct snd_sgio2audio_chan *chan = substream->runtime->private_data;
	int ch = chan->idx;

	/* reset DMA channel */
	writeq(CHANNEL_CONTROL_RESET, &mace->perif.audio.chan[ch].control);
	udelay(10);
	writeq(0, &mace->perif.audio.chan[ch].control);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/* push a full buffer */
		snd_sgio2audio_dma_push_frag(chip, ch, CHANNEL_RING_SIZE - 32);
	}
	/* set DMA to wake on 50% empty and enable interrupt */
	writeq(CHANNEL_DMA_ENABLE | CHANNEL_INT_THRESHOLD_50,
	       &mace->perif.audio.chan[ch].control);
	return 0;
}