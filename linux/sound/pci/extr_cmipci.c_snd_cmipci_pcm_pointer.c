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
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct cmipci_pcm {unsigned int dma_size; unsigned int shift; size_t offset; scalar_t__ ch; int /*<<< orphan*/  running; } ;
struct cmipci {TYPE_1__* card; } ;
typedef  size_t snd_pcm_uframes_t ;
struct TYPE_4__ {int channels; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CM_REG_CH0_FRAME1 ; 
 unsigned int CM_REG_CH0_FRAME2 ; 
 unsigned int CM_REG_CH1_FRAME1 ; 
 unsigned int CM_REG_CH1_FRAME2 ; 
 size_t SNDRV_PCM_POS_XRUN ; 
 size_t bytes_to_frames (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 size_t snd_cmipci_read (struct cmipci*,unsigned int) ; 
 unsigned int snd_cmipci_read_w (struct cmipci*,unsigned int) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_cmipci_pcm_pointer(struct cmipci *cm, struct cmipci_pcm *rec,
						struct snd_pcm_substream *substream)
{
	size_t ptr;
	unsigned int reg, rem, tries;

	if (!rec->running)
		return 0;
#if 1 // this seems better..
	reg = rec->ch ? CM_REG_CH1_FRAME2 : CM_REG_CH0_FRAME2;
	for (tries = 0; tries < 3; tries++) {
		rem = snd_cmipci_read_w(cm, reg);
		if (rem < rec->dma_size)
			goto ok;
	} 
	dev_err(cm->card->dev, "invalid PCM pointer: %#x\n", rem);
	return SNDRV_PCM_POS_XRUN;
ok:
	ptr = (rec->dma_size - (rem + 1)) >> rec->shift;
#else
	reg = rec->ch ? CM_REG_CH1_FRAME1 : CM_REG_CH0_FRAME1;
	ptr = snd_cmipci_read(cm, reg) - rec->offset;
	ptr = bytes_to_frames(substream->runtime, ptr);
#endif
	if (substream->runtime->channels > 2)
		ptr = (ptr * 2) / substream->runtime->channels;
	return ptr;
}