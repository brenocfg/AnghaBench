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
struct snd_gus_voice {int /*<<< orphan*/  (* handler_volume ) (struct snd_gus_card*,struct snd_gus_voice*) ;int /*<<< orphan*/  interrupt_stat_volume; int /*<<< orphan*/  (* handler_wave ) (struct snd_gus_card*,struct snd_gus_voice*) ;int /*<<< orphan*/  interrupt_stat_wave; scalar_t__ use; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* interrupt_handler_dma_read ) (struct snd_gus_card*) ;int /*<<< orphan*/  interrupt_stat_dma_read; int /*<<< orphan*/  (* interrupt_handler_dma_write ) (struct snd_gus_card*) ;int /*<<< orphan*/  interrupt_stat_dma_write; int /*<<< orphan*/  (* interrupt_handler_timer2 ) (struct snd_gus_card*) ;int /*<<< orphan*/  interrupt_stat_timer2; int /*<<< orphan*/  (* interrupt_handler_timer1 ) (struct snd_gus_card*) ;int /*<<< orphan*/  interrupt_stat_timer1; int /*<<< orphan*/  interrupt_stat_voice_lost; struct snd_gus_voice* voices; int /*<<< orphan*/  (* interrupt_handler_midi_out ) (struct snd_gus_card*) ;int /*<<< orphan*/  interrupt_stat_midi_out; int /*<<< orphan*/  (* interrupt_handler_midi_in ) (struct snd_gus_card*) ;int /*<<< orphan*/  interrupt_stat_midi_in; int /*<<< orphan*/  reg_irqstat; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_DRAM_DMA_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_REC_DMA_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_VOICES_IRQ ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_ADDRESS_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_CONTROL ; 
 int /*<<< orphan*/  STAT_ADD (int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_i_ctrl_stop (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int snd_gf1_i_look8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 unsigned char snd_gf1_i_read8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_gus_card*) ; 
 int /*<<< orphan*/  stub2 (struct snd_gus_card*) ; 
 int /*<<< orphan*/  stub3 (struct snd_gus_card*,struct snd_gus_voice*) ; 
 int /*<<< orphan*/  stub4 (struct snd_gus_card*,struct snd_gus_voice*) ; 
 int /*<<< orphan*/  stub5 (struct snd_gus_card*) ; 
 int /*<<< orphan*/  stub6 (struct snd_gus_card*) ; 
 int /*<<< orphan*/  stub7 (struct snd_gus_card*) ; 
 int /*<<< orphan*/  stub8 (struct snd_gus_card*) ; 

irqreturn_t snd_gus_interrupt(int irq, void *dev_id)
{
	struct snd_gus_card * gus = dev_id;
	unsigned char status;
	int loop = 100;
	int handled = 0;

__again:
	status = inb(gus->gf1.reg_irqstat);
	if (status == 0)
		return IRQ_RETVAL(handled);
	handled = 1;
	/* snd_printk(KERN_DEBUG "IRQ: status = 0x%x\n", status); */
	if (status & 0x02) {
		STAT_ADD(gus->gf1.interrupt_stat_midi_in);
		if (gus->gf1.interrupt_handler_midi_in)
			gus->gf1.interrupt_handler_midi_in(gus);
	}
	if (status & 0x01) {
		STAT_ADD(gus->gf1.interrupt_stat_midi_out);
		if (gus->gf1.interrupt_handler_midi_out)
			gus->gf1.interrupt_handler_midi_out(gus);
	}
	if (status & (0x20 | 0x40)) {
		unsigned int already, _current_;
		unsigned char voice_status, voice;
		struct snd_gus_voice *pvoice;

		already = 0;
		while (((voice_status = snd_gf1_i_read8(gus, SNDRV_GF1_GB_VOICES_IRQ)) & 0xc0) != 0xc0) {
			voice = voice_status & 0x1f;
			_current_ = 1 << voice;
			if (already & _current_)
				continue;	/* multi request */
			already |= _current_;	/* mark request */
#if 0
			printk(KERN_DEBUG "voice = %i, voice_status = 0x%x, "
			       "voice_verify = %i\n",
			       voice, voice_status, inb(GUSP(gus, GF1PAGE)));
#endif
			pvoice = &gus->gf1.voices[voice]; 
			if (pvoice->use) {
				if (!(voice_status & 0x80)) {	/* voice position IRQ */
					STAT_ADD(pvoice->interrupt_stat_wave);
					pvoice->handler_wave(gus, pvoice);
				}
				if (!(voice_status & 0x40)) {	/* volume ramp IRQ */
					STAT_ADD(pvoice->interrupt_stat_volume);
					pvoice->handler_volume(gus, pvoice);
				}
			} else {
				STAT_ADD(gus->gf1.interrupt_stat_voice_lost);
				snd_gf1_i_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
				snd_gf1_i_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
			}
		}
	}
	if (status & 0x04) {
		STAT_ADD(gus->gf1.interrupt_stat_timer1);
		if (gus->gf1.interrupt_handler_timer1)
			gus->gf1.interrupt_handler_timer1(gus);
	}
	if (status & 0x08) {
		STAT_ADD(gus->gf1.interrupt_stat_timer2);
		if (gus->gf1.interrupt_handler_timer2)
			gus->gf1.interrupt_handler_timer2(gus);
	}
	if (status & 0x80) {
		if (snd_gf1_i_look8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL) & 0x40) {
			STAT_ADD(gus->gf1.interrupt_stat_dma_write);
			if (gus->gf1.interrupt_handler_dma_write)
				gus->gf1.interrupt_handler_dma_write(gus);
		}
		if (snd_gf1_i_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL) & 0x40) {
			STAT_ADD(gus->gf1.interrupt_stat_dma_read);
			if (gus->gf1.interrupt_handler_dma_read)
				gus->gf1.interrupt_handler_dma_read(gus);
		}
	}
	if (--loop > 0)
		goto __again;
	return IRQ_NONE;
}