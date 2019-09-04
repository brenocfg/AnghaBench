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
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; struct nuc900_audio* private_data; } ;
struct nuc900_audio {int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ ACTL_RESET ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 int EINVAL ; 
 unsigned long PLAY_LEFT_CHNNEL ; 
 unsigned long PLAY_RIGHT_CHNNEL ; 
 unsigned long RECORD_LEFT_CHNNEL ; 
 unsigned long RECORD_RIGHT_CHNNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  nuc900_update_dma_register (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nuc900_dma_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nuc900_audio *nuc900_audio = runtime->private_data;
	unsigned long flags, val;
	int ret = 0;

	spin_lock_irqsave(&nuc900_audio->lock, flags);

	nuc900_update_dma_register(substream);

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);

	switch (runtime->channels) {
	case 1:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			val &= ~(PLAY_LEFT_CHNNEL | PLAY_RIGHT_CHNNEL);
			val |= PLAY_RIGHT_CHNNEL;
		} else {
			val &= ~(RECORD_LEFT_CHNNEL | RECORD_RIGHT_CHNNEL);
			val |= RECORD_RIGHT_CHNNEL;
		}
		AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);
		break;
	case 2:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			val |= (PLAY_LEFT_CHNNEL | PLAY_RIGHT_CHNNEL);
		else
			val |= (RECORD_LEFT_CHNNEL | RECORD_RIGHT_CHNNEL);
		AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);
		break;
	default:
		ret = -EINVAL;
	}
	spin_unlock_irqrestore(&nuc900_audio->lock, flags);
	return ret;
}