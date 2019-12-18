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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct cs4281_dma {int valDCR; int valFCR; int valDMR; int /*<<< orphan*/  regDCR; int /*<<< orphan*/  regFCR; int /*<<< orphan*/  regDMR; } ;
struct cs4281 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct cs4281_dma* private_data; } ;

/* Variables and functions */
 int BA0_DCR_MSK ; 
 int BA0_DMR_DMA ; 
 int BA0_DMR_POLL ; 
 int /*<<< orphan*/  BA0_FCR0 ; 
 int BA0_FCR_FEN ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,int) ; 
 struct cs4281* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cs4281_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct cs4281_dma *dma = substream->runtime->private_data;
	struct cs4281 *chip = snd_pcm_substream_chip(substream);

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dma->valDCR |= BA0_DCR_MSK;
		dma->valFCR |= BA0_FCR_FEN;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dma->valDCR &= ~BA0_DCR_MSK;
		dma->valFCR &= ~BA0_FCR_FEN;
		break;
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		snd_cs4281_pokeBA0(chip, dma->regDMR, dma->valDMR & ~BA0_DMR_DMA);
		dma->valDMR |= BA0_DMR_DMA;
		dma->valDCR &= ~BA0_DCR_MSK;
		dma->valFCR |= BA0_FCR_FEN;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		dma->valDMR &= ~(BA0_DMR_DMA|BA0_DMR_POLL);
		dma->valDCR |= BA0_DCR_MSK;
		dma->valFCR &= ~BA0_FCR_FEN;
		/* Leave wave playback FIFO enabled for FM */
		if (dma->regFCR != BA0_FCR0)
			dma->valFCR &= ~BA0_FCR_FEN;
		break;
	default:
		spin_unlock(&chip->reg_lock);
		return -EINVAL;
	}
	snd_cs4281_pokeBA0(chip, dma->regDMR, dma->valDMR);
	snd_cs4281_pokeBA0(chip, dma->regFCR, dma->valFCR);
	snd_cs4281_pokeBA0(chip, dma->regDCR, dma->valDCR);
	spin_unlock(&chip->reg_lock);
	return 0;
}