#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct es1938 {int active; TYPE_5__* rmidi; TYPE_4__* master_volume; TYPE_6__* card; TYPE_3__* master_switch; TYPE_2__* hw_volume; TYPE_1__* hw_switch; int /*<<< orphan*/  playback1_substream; int /*<<< orphan*/  playback2_substream; int /*<<< orphan*/  capture_substream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  private_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ADC1 ; 
 int /*<<< orphan*/  AUDIO2DMAADDR ; 
 int /*<<< orphan*/  AUDIO2DMACOUNT ; 
 int DAC1 ; 
 int DAC2 ; 
 int /*<<< orphan*/  DMAADDR ; 
 int /*<<< orphan*/  DMACOUNT ; 
 int /*<<< orphan*/  DMASTATUS ; 
 int /*<<< orphan*/  ESSSB_IREG_AUDIO2CONTROL2 ; 
 int /*<<< orphan*/  IRQCONTROL ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  SLDM_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIO_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLSB_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 unsigned char inl (int /*<<< orphan*/ ) ; 
 unsigned char inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_notify (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_es1938_mixer_bits (struct es1938*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_es1938_mixer_read (struct es1938*,int) ; 
 int /*<<< orphan*/  snd_es1938_mixer_write (struct es1938*,int,int) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snd_es1938_interrupt(int irq, void *dev_id)
{
	struct es1938 *chip = dev_id;
	unsigned char status, audiostatus;
	int handled = 0;

	status = inb(SLIO_REG(chip, IRQCONTROL));
#if 0
	dev_dbg(chip->card->dev,
		"Es1938debug - interrupt status: =0x%x\n", status);
#endif
	
	/* AUDIO 1 */
	if (status & 0x10) {
#if 0
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 interrupt\n");
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 DMAC DMA count: %u\n",
		       inw(SLDM_REG(chip, DMACOUNT)));
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 DMAC DMA base: %u\n",
		       inl(SLDM_REG(chip, DMAADDR)));
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 DMAC DMA status: 0x%x\n",
		       inl(SLDM_REG(chip, DMASTATUS)));
#endif
		/* clear irq */
		handled = 1;
		audiostatus = inb(SLSB_REG(chip, STATUS));
		if (chip->active & ADC1)
			snd_pcm_period_elapsed(chip->capture_substream);
		else if (chip->active & DAC1)
			snd_pcm_period_elapsed(chip->playback2_substream);
	}
	
	/* AUDIO 2 */
	if (status & 0x20) {
#if 0
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 2 interrupt\n");
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 2 DMAC DMA count: %u\n",
		       inw(SLIO_REG(chip, AUDIO2DMACOUNT)));
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 2 DMAC DMA base: %u\n",
		       inl(SLIO_REG(chip, AUDIO2DMAADDR)));

#endif
		/* clear irq */
		handled = 1;
		snd_es1938_mixer_bits(chip, ESSSB_IREG_AUDIO2CONTROL2, 0x80, 0);
		if (chip->active & DAC2)
			snd_pcm_period_elapsed(chip->playback1_substream);
	}

	/* Hardware volume */
	if (status & 0x40) {
		int split = snd_es1938_mixer_read(chip, 0x64) & 0x80;
		handled = 1;
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE, &chip->hw_switch->id);
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE, &chip->hw_volume->id);
		if (!split) {
			snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_switch->id);
			snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_volume->id);
		}
		/* ack interrupt */
		snd_es1938_mixer_write(chip, 0x66, 0x00);
	}

	/* MPU401 */
	if (status & 0x80) {
		// the following line is evil! It switches off MIDI interrupt handling after the first interrupt received.
		// replacing the last 0 by 0x40 works for ESS-Solo1, but just doing nothing works as well!
		// andreas@flying-snail.de
		// snd_es1938_mixer_bits(chip, ESSSB_IREG_MPU401CONTROL, 0x40, 0); /* ack? */
		if (chip->rmidi) {
			handled = 1;
			snd_mpu401_uart_interrupt(irq, chip->rmidi->private_data);
		}
	}
	return IRQ_RETVAL(handled);
}