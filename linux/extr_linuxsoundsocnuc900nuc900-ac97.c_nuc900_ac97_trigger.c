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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct nuc900_audio {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ ACTL_ACOS0 ; 
 scalar_t__ ACTL_PSR ; 
 scalar_t__ ACTL_RESET ; 
 scalar_t__ ACTL_RSR ; 
 unsigned long AC_PLAY ; 
 unsigned long AC_RECORD ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 int EINVAL ; 
 unsigned long P_DMA_END_IRQ ; 
 unsigned long P_DMA_MIDDLE_IRQ ; 
 unsigned long RESET_PRSR ; 
 unsigned long R_DMA_END_IRQ ; 
 unsigned long R_DMA_MIDDLE_IRQ ; 
 unsigned long SLOT3_VALID ; 
 unsigned long SLOT4_VALID ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 unsigned long VALID_FRAME ; 
 struct nuc900_audio* nuc900_ac97_data ; 

__attribute__((used)) static int nuc900_ac97_trigger(struct snd_pcm_substream *substream,
				int cmd, struct snd_soc_dai *dai)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;
	int ret;
	unsigned long val, tmp;

	ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			tmp = AUDIO_READ(nuc900_audio->mmio + ACTL_ACOS0);
			tmp |= (SLOT3_VALID | SLOT4_VALID | VALID_FRAME);
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS0, tmp);

			tmp = AUDIO_READ(nuc900_audio->mmio + ACTL_PSR);
			tmp |= (P_DMA_END_IRQ | P_DMA_MIDDLE_IRQ);
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_PSR, tmp);
			val |= AC_PLAY;
		} else {
			tmp = AUDIO_READ(nuc900_audio->mmio + ACTL_RSR);
			tmp |= (R_DMA_END_IRQ | R_DMA_MIDDLE_IRQ);

			AUDIO_WRITE(nuc900_audio->mmio + ACTL_RSR, tmp);
			val |= AC_RECORD;
		}

		AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);

		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			tmp = AUDIO_READ(nuc900_audio->mmio + ACTL_ACOS0);
			tmp &= ~(SLOT3_VALID | SLOT4_VALID);
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS0, tmp);

			AUDIO_WRITE(nuc900_audio->mmio + ACTL_PSR, RESET_PRSR);
			val &= ~AC_PLAY;
		} else {
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_RSR, RESET_PRSR);
			val &= ~AC_RECORD;
		}

		AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);

		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}