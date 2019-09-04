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
struct snd_ice1712 {scalar_t__ capture_con_substream; scalar_t__ playback_con_substream; scalar_t__* playback_con_substream_ds; scalar_t__ capture_pro_substream; scalar_t__ playback_pro_substream; int /*<<< orphan*/  reg_lock; scalar_t__ midi_input; scalar_t__ midi_output; TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FIFO_ERR ; 
 int /*<<< orphan*/  DMA_INT_MASK ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ ; 
 int /*<<< orphan*/  IRQSTAT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 unsigned char VT1724_IRQ_MPU_RX ; 
 unsigned char VT1724_IRQ_MPU_TX ; 
 unsigned char VT1724_IRQ_MTPCM ; 
 unsigned char VT1724_MULTI_FIFO_ERR ; 
 unsigned char VT1724_MULTI_PDMA0 ; 
 unsigned char VT1724_MULTI_PDMA1 ; 
 unsigned char VT1724_MULTI_PDMA2 ; 
 unsigned char VT1724_MULTI_PDMA3 ; 
 unsigned char VT1724_MULTI_PDMA4 ; 
 unsigned char VT1724_MULTI_RDMA0 ; 
 unsigned char VT1724_MULTI_RDMA1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  enable_midi_irq (struct snd_ice1712*,unsigned char,int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt1724_midi_clear_rx (struct snd_ice1712*) ; 
 int /*<<< orphan*/  vt1724_midi_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  vt1724_midi_write (struct snd_ice1712*) ; 

__attribute__((used)) static irqreturn_t snd_vt1724_interrupt(int irq, void *dev_id)
{
	struct snd_ice1712 *ice = dev_id;
	unsigned char status;
	unsigned char status_mask =
		VT1724_IRQ_MPU_RX | VT1724_IRQ_MPU_TX | VT1724_IRQ_MTPCM;
	int handled = 0;
	int timeout = 0;

	while (1) {
		status = inb(ICEREG1724(ice, IRQSTAT));
		status &= status_mask;
		if (status == 0)
			break;
		spin_lock(&ice->reg_lock);
		if (++timeout > 10) {
			status = inb(ICEREG1724(ice, IRQSTAT));
			dev_err(ice->card->dev,
				"Too long irq loop, status = 0x%x\n", status);
			if (status & VT1724_IRQ_MPU_TX) {
				dev_err(ice->card->dev, "Disabling MPU_TX\n");
				enable_midi_irq(ice, VT1724_IRQ_MPU_TX, 0);
			}
			spin_unlock(&ice->reg_lock);
			break;
		}
		handled = 1;
		if (status & VT1724_IRQ_MPU_TX) {
			if (ice->midi_output)
				vt1724_midi_write(ice);
			else
				enable_midi_irq(ice, VT1724_IRQ_MPU_TX, 0);
			/* Due to mysterical reasons, MPU_TX is always
			 * generated (and can't be cleared) when a PCM
			 * playback is going.  So let's ignore at the
			 * next loop.
			 */
			status_mask &= ~VT1724_IRQ_MPU_TX;
		}
		if (status & VT1724_IRQ_MPU_RX) {
			if (ice->midi_input)
				vt1724_midi_read(ice);
			else
				vt1724_midi_clear_rx(ice);
		}
		/* ack MPU irq */
		outb(status, ICEREG1724(ice, IRQSTAT));
		spin_unlock(&ice->reg_lock);
		if (status & VT1724_IRQ_MTPCM) {
			/*
			 * Multi-track PCM
			 * PCM assignment are:
			 * Playback DMA0 (M/C) = playback_pro_substream
			 * Playback DMA1 = playback_con_substream_ds[0]
			 * Playback DMA2 = playback_con_substream_ds[1]
			 * Playback DMA3 = playback_con_substream_ds[2]
			 * Playback DMA4 (SPDIF) = playback_con_substream
			 * Record DMA0 = capture_pro_substream
			 * Record DMA1 = capture_con_substream
			 */
			unsigned char mtstat = inb(ICEMT1724(ice, IRQ));
			if (mtstat & VT1724_MULTI_PDMA0) {
				if (ice->playback_pro_substream)
					snd_pcm_period_elapsed(ice->playback_pro_substream);
			}
			if (mtstat & VT1724_MULTI_RDMA0) {
				if (ice->capture_pro_substream)
					snd_pcm_period_elapsed(ice->capture_pro_substream);
			}
			if (mtstat & VT1724_MULTI_PDMA1) {
				if (ice->playback_con_substream_ds[0])
					snd_pcm_period_elapsed(ice->playback_con_substream_ds[0]);
			}
			if (mtstat & VT1724_MULTI_PDMA2) {
				if (ice->playback_con_substream_ds[1])
					snd_pcm_period_elapsed(ice->playback_con_substream_ds[1]);
			}
			if (mtstat & VT1724_MULTI_PDMA3) {
				if (ice->playback_con_substream_ds[2])
					snd_pcm_period_elapsed(ice->playback_con_substream_ds[2]);
			}
			if (mtstat & VT1724_MULTI_PDMA4) {
				if (ice->playback_con_substream)
					snd_pcm_period_elapsed(ice->playback_con_substream);
			}
			if (mtstat & VT1724_MULTI_RDMA1) {
				if (ice->capture_con_substream)
					snd_pcm_period_elapsed(ice->capture_con_substream);
			}
			/* ack anyway to avoid freeze */
			outb(mtstat, ICEMT1724(ice, IRQ));
			/* ought to really handle this properly */
			if (mtstat & VT1724_MULTI_FIFO_ERR) {
				unsigned char fstat = inb(ICEMT1724(ice, DMA_FIFO_ERR));
				outb(fstat, ICEMT1724(ice, DMA_FIFO_ERR));
				outb(VT1724_MULTI_FIFO_ERR | inb(ICEMT1724(ice, DMA_INT_MASK)), ICEMT1724(ice, DMA_INT_MASK));
				/* If I don't do this, I get machine lockup due to continual interrupts */
			}

		}
	}
	return IRQ_RETVAL(handled);
}