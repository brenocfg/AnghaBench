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
struct snd_es18xx {int caps; int active; TYPE_5__* master_volume; TYPE_4__* master_switch; TYPE_3__* hw_volume; TYPE_2__* hw_switch; TYPE_1__* rmidi; scalar_t__ port; int /*<<< orphan*/  playback_b_substream; int /*<<< orphan*/  capture_a_substream; int /*<<< orphan*/  playback_a_substream; scalar_t__ ctrl_port; } ;
struct snd_card {struct snd_es18xx* private_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ADC1 ; 
 unsigned char AUDIO1_IRQ ; 
 unsigned char AUDIO2_IRQ ; 
 int DAC1 ; 
 int DAC2 ; 
 int ES18XX_CONTROL ; 
 int ES18XX_HWV ; 
 unsigned char HWV_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char MPU_IRQ ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_es18xx_mixer_bits (struct snd_es18xx*,int,int,int) ; 
 int snd_es18xx_mixer_read (struct snd_es18xx*,int) ; 
 int /*<<< orphan*/  snd_es18xx_mixer_write (struct snd_es18xx*,int,int) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snd_es18xx_interrupt(int irq, void *dev_id)
{
	struct snd_card *card = dev_id;
	struct snd_es18xx *chip = card->private_data;
	unsigned char status;

	if (chip->caps & ES18XX_CONTROL) {
		/* Read Interrupt status */
		status = inb(chip->ctrl_port + 6);
	} else {
		/* Read Interrupt status */
		status = snd_es18xx_mixer_read(chip, 0x7f) >> 4;
	}
#if 0
	else {
		status = 0;
		if (inb(chip->port + 0x0C) & 0x01)
			status |= AUDIO1_IRQ;
		if (snd_es18xx_mixer_read(chip, 0x7A) & 0x80)
			status |= AUDIO2_IRQ;
		if ((chip->caps & ES18XX_HWV) &&
		    snd_es18xx_mixer_read(chip, 0x64) & 0x10)
			status |= HWV_IRQ;
	}
#endif

	/* Audio 1 & Audio 2 */
        if (status & AUDIO2_IRQ) {
                if (chip->active & DAC2)
                	snd_pcm_period_elapsed(chip->playback_a_substream);
		/* ack interrupt */
                snd_es18xx_mixer_bits(chip, 0x7A, 0x80, 0x00);
        }
        if (status & AUDIO1_IRQ) {
                /* ok.. capture is active */
                if (chip->active & ADC1)
                	snd_pcm_period_elapsed(chip->capture_a_substream);
                /* ok.. playback2 is active */
                else if (chip->active & DAC1)
                	snd_pcm_period_elapsed(chip->playback_b_substream);
		/* ack interrupt */
		inb(chip->port + 0x0E);
        }

	/* MPU */
	if ((status & MPU_IRQ) && chip->rmidi)
		snd_mpu401_uart_interrupt(irq, chip->rmidi->private_data);

	/* Hardware volume */
	if (status & HWV_IRQ) {
		int split = 0;
		if (chip->caps & ES18XX_HWV) {
			split = snd_es18xx_mixer_read(chip, 0x64) & 0x80;
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->hw_switch->id);
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->hw_volume->id);
		}
		if (!split) {
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_switch->id);
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_volume->id);
		}
		/* ack interrupt */
		snd_es18xx_mixer_write(chip, 0x66, 0x00);
	}
	return IRQ_HANDLED;
}