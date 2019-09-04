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
typedef  int uint32_t ;
struct snd_ps3_card_info {int null_buffer_start_dma_addr; int /*<<< orphan*/  dma_lock; void** dma_next_transfer_vaddr; } ;
typedef  enum snd_ps3_dma_filltype { ____Placeholder_snd_ps3_dma_filltype } snd_ps3_dma_filltype ;
typedef  enum snd_ps3_ch { ____Placeholder_snd_ps3_ch } snd_ps3_ch ;

/* Variables and functions */
 int PS3_AUDIO_AO_3W_LDATA (int /*<<< orphan*/ ) ; 
 int PS3_AUDIO_AO_3W_RDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS3_AUDIO_DEST (int) ; 
 int PS3_AUDIO_DEST_TARGET_AUDIOFIFO ; 
 int /*<<< orphan*/  PS3_AUDIO_DMAC_BLOCK_SIZE ; 
 int /*<<< orphan*/  PS3_AUDIO_DMASIZE (int) ; 
 int /*<<< orphan*/  PS3_AUDIO_KICK (int) ; 
 int PS3_AUDIO_KICK_EVENT_ALWAYS ; 
 int PS3_AUDIO_KICK_EVENT_AUDIO_DMA (int) ; 
 int PS3_AUDIO_KICK_EVENT_SERIALOUT0_EMPTY ; 
 int PS3_AUDIO_KICK_REQUEST ; 
 int /*<<< orphan*/  PS3_AUDIO_SOURCE (int) ; 
 int PS3_AUDIO_SOURCE_TARGET_SYSTEM_MEMORY ; 
#define  SND_PS3_DMA_FILLTYPE_FIRSTFILL 131 
#define  SND_PS3_DMA_FILLTYPE_RUNNING 130 
#define  SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL 129 
#define  SND_PS3_DMA_FILLTYPE_SILENT_RUNNING 128 
 int /*<<< orphan*/  snd_ps3_bump_buffer (struct snd_ps3_card_info*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ps3_verify_dma_stop (struct snd_ps3_card_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int v_to_bus (struct snd_ps3_card_info*,void*,int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_ps3_program_dma(struct snd_ps3_card_info *card,
			       enum snd_ps3_dma_filltype filltype)
{
	/* this dmac does not support over 4G */
	uint32_t dma_addr;
	int fill_stages, dma_ch, stage;
	enum snd_ps3_ch ch;
	uint32_t ch0_kick_event = 0; /* initialize to mute gcc */
	void *start_vaddr;
	unsigned long irqsave;
	int silent = 0;

	switch (filltype) {
	case SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL:
		silent = 1;
		/* intentionally fall thru */
	case SND_PS3_DMA_FILLTYPE_FIRSTFILL:
		ch0_kick_event = PS3_AUDIO_KICK_EVENT_ALWAYS;
		break;

	case SND_PS3_DMA_FILLTYPE_SILENT_RUNNING:
		silent = 1;
		/* intentionally fall thru */
	case SND_PS3_DMA_FILLTYPE_RUNNING:
		ch0_kick_event = PS3_AUDIO_KICK_EVENT_SERIALOUT0_EMPTY;
		break;
	}

	snd_ps3_verify_dma_stop(card, 700, 0);
	fill_stages = 4;
	spin_lock_irqsave(&card->dma_lock, irqsave);
	for (ch = 0; ch < 2; ch++) {
		start_vaddr = card->dma_next_transfer_vaddr[0];
		for (stage = 0; stage < fill_stages; stage++) {
			dma_ch = stage * 2 + ch;
			if (silent)
				dma_addr = card->null_buffer_start_dma_addr;
			else
				dma_addr =
				v_to_bus(card,
					 card->dma_next_transfer_vaddr[ch],
					 ch);

			write_reg(PS3_AUDIO_SOURCE(dma_ch),
				  (PS3_AUDIO_SOURCE_TARGET_SYSTEM_MEMORY |
				   dma_addr));

			/* dst: fixed to 3wire#0 */
			if (ch == 0)
				write_reg(PS3_AUDIO_DEST(dma_ch),
					  (PS3_AUDIO_DEST_TARGET_AUDIOFIFO |
					   PS3_AUDIO_AO_3W_LDATA(0)));
			else
				write_reg(PS3_AUDIO_DEST(dma_ch),
					  (PS3_AUDIO_DEST_TARGET_AUDIOFIFO |
					   PS3_AUDIO_AO_3W_RDATA(0)));

			/* count always 1 DMA block (1/2 stage = 128 bytes) */
			write_reg(PS3_AUDIO_DMASIZE(dma_ch), 0);
			/* bump pointer if needed */
			if (!silent)
				snd_ps3_bump_buffer(card, ch,
						    PS3_AUDIO_DMAC_BLOCK_SIZE,
						    stage);

			/* kick event  */
			if (dma_ch == 0)
				write_reg(PS3_AUDIO_KICK(dma_ch),
					  ch0_kick_event);
			else
				write_reg(PS3_AUDIO_KICK(dma_ch),
					  PS3_AUDIO_KICK_EVENT_AUDIO_DMA(dma_ch
									 - 1) |
					  PS3_AUDIO_KICK_REQUEST);
		}
	}
	/* ensure the hardware sees the change */
	wmb();
	spin_unlock_irqrestore(&card->dma_lock, irqsave);

	return 0;
}