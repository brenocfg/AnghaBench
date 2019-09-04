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
struct snd_ps3_card_info {int running; int /*<<< orphan*/  dma_lock; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_AUDIO_AX_IS ; 
 int /*<<< orphan*/  PS3_AUDIO_KICK (int) ; 
 int PS3_AUDIO_KICK_STATUS_MASK ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL ; 
 int /*<<< orphan*/  SND_PS3_DMA_FILLTYPE_SILENT_RUNNING ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 struct snd_ps3_card_info* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ps3_kick_dma (struct snd_ps3_card_info*) ; 
 int /*<<< orphan*/  snd_ps3_program_dma (struct snd_ps3_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ps3_wait_for_dma_stop (struct snd_ps3_card_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ps3_pcm_trigger(struct snd_pcm_substream *substream,
			       int cmd)
{
	struct snd_ps3_card_info *card = snd_pcm_substream_chip(substream);
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		/* clear outstanding interrupts  */
		update_reg(PS3_AUDIO_AX_IS, 0);

		spin_lock(&card->dma_lock);
		{
			card->running = 1;
		}
		spin_unlock(&card->dma_lock);

		snd_ps3_program_dma(card,
				    SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL);
		snd_ps3_kick_dma(card);
		while (read_reg(PS3_AUDIO_KICK(7)) &
		       PS3_AUDIO_KICK_STATUS_MASK) {
			udelay(1);
		}
		snd_ps3_program_dma(card, SND_PS3_DMA_FILLTYPE_SILENT_RUNNING);
		snd_ps3_kick_dma(card);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		spin_lock(&card->dma_lock);
		{
			card->running = 0;
		}
		spin_unlock(&card->dma_lock);
		snd_ps3_wait_for_dma_stop(card);
		break;
	default:
		break;

	}

	return ret;
}