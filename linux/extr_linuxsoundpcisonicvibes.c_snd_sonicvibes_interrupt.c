#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sonicvibes {TYPE_3__* master_volume; TYPE_4__* card; TYPE_2__* master_mute; int /*<<< orphan*/  reg_lock; TYPE_1__* rmidi; int /*<<< orphan*/  capture_substream; int /*<<< orphan*/  playback_substream; scalar_t__ pcm; int /*<<< orphan*/  irqmask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQMASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  STATUS ; 
 unsigned char SV_DMAA_IRQ ; 
 unsigned char SV_DMAC_IRQ ; 
 int /*<<< orphan*/  SV_IREG_LEFT_ANALOG ; 
 int /*<<< orphan*/  SV_IREG_RIGHT_ANALOG ; 
 int /*<<< orphan*/  SV_IREG_UD_BUTTON ; 
 unsigned char SV_MIDI_IRQ ; 
 int /*<<< orphan*/  SV_REG (struct sonicvibes*,int /*<<< orphan*/ ) ; 
 unsigned char SV_UD_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_notify (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 void* snd_sonicvibes_in1 (struct sonicvibes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sonicvibes_out1 (struct sonicvibes*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_sonicvibes_interrupt(int irq, void *dev_id)
{
	struct sonicvibes *sonic = dev_id;
	unsigned char status;

	status = inb(SV_REG(sonic, STATUS));
	if (!(status & (SV_DMAA_IRQ | SV_DMAC_IRQ | SV_MIDI_IRQ)))
		return IRQ_NONE;
	if (status == 0xff) {	/* failure */
		outb(sonic->irqmask = ~0, SV_REG(sonic, IRQMASK));
		dev_err(sonic->card->dev,
			"IRQ failure - interrupts disabled!!\n");
		return IRQ_HANDLED;
	}
	if (sonic->pcm) {
		if (status & SV_DMAA_IRQ)
			snd_pcm_period_elapsed(sonic->playback_substream);
		if (status & SV_DMAC_IRQ)
			snd_pcm_period_elapsed(sonic->capture_substream);
	}
	if (sonic->rmidi) {
		if (status & SV_MIDI_IRQ)
			snd_mpu401_uart_interrupt(irq, sonic->rmidi->private_data);
	}
	if (status & SV_UD_IRQ) {
		unsigned char udreg;
		int vol, oleft, oright, mleft, mright;

		spin_lock(&sonic->reg_lock);
		udreg = snd_sonicvibes_in1(sonic, SV_IREG_UD_BUTTON);
		vol = udreg & 0x3f;
		if (!(udreg & 0x40))
			vol = -vol;
		oleft = mleft = snd_sonicvibes_in1(sonic, SV_IREG_LEFT_ANALOG);
		oright = mright = snd_sonicvibes_in1(sonic, SV_IREG_RIGHT_ANALOG);
		oleft &= 0x1f;
		oright &= 0x1f;
		oleft += vol;
		if (oleft < 0)
			oleft = 0;
		if (oleft > 0x1f)
			oleft = 0x1f;
		oright += vol;
		if (oright < 0)
			oright = 0;
		if (oright > 0x1f)
			oright = 0x1f;
		if (udreg & 0x80) {
			mleft ^= 0x80;
			mright ^= 0x80;
		}
		oleft |= mleft & 0x80;
		oright |= mright & 0x80;
		snd_sonicvibes_out1(sonic, SV_IREG_LEFT_ANALOG, oleft);
		snd_sonicvibes_out1(sonic, SV_IREG_RIGHT_ANALOG, oright);
		spin_unlock(&sonic->reg_lock);
		snd_ctl_notify(sonic->card, SNDRV_CTL_EVENT_MASK_VALUE, &sonic->master_mute->id);
		snd_ctl_notify(sonic->card, SNDRV_CTL_EVENT_MASK_VALUE, &sonic->master_volume->id);
	}
	return IRQ_HANDLED;
}