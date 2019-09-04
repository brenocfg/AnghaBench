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
struct cmipci {TYPE_2__* channel; scalar_t__ pcm; TYPE_1__* rmidi; int /*<<< orphan*/  reg_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  substream; scalar_t__ running; } ;
struct TYPE_3__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 unsigned int CM_CH0_INT_EN ; 
 unsigned int CM_CH1_INT_EN ; 
 unsigned int CM_CHINT0 ; 
 unsigned int CM_CHINT1 ; 
 unsigned int CM_INTR ; 
 int /*<<< orphan*/  CM_REG_INT_HLDCLR ; 
 int /*<<< orphan*/  CM_REG_INT_STATUS ; 
 unsigned int CM_UARTINT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int snd_cmipci_read (struct cmipci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_cmipci_interrupt(int irq, void *dev_id)
{
	struct cmipci *cm = dev_id;
	unsigned int status, mask = 0;
	
	/* fastpath out, to ease interrupt sharing */
	status = snd_cmipci_read(cm, CM_REG_INT_STATUS);
	if (!(status & CM_INTR))
		return IRQ_NONE;

	/* acknowledge interrupt */
	spin_lock(&cm->reg_lock);
	if (status & CM_CHINT0)
		mask |= CM_CH0_INT_EN;
	if (status & CM_CHINT1)
		mask |= CM_CH1_INT_EN;
	snd_cmipci_clear_bit(cm, CM_REG_INT_HLDCLR, mask);
	snd_cmipci_set_bit(cm, CM_REG_INT_HLDCLR, mask);
	spin_unlock(&cm->reg_lock);

	if (cm->rmidi && (status & CM_UARTINT))
		snd_mpu401_uart_interrupt(irq, cm->rmidi->private_data);

	if (cm->pcm) {
		if ((status & CM_CHINT0) && cm->channel[0].running)
			snd_pcm_period_elapsed(cm->channel[0].substream);
		if ((status & CM_CHINT1) && cm->channel[1].running)
			snd_pcm_period_elapsed(cm->channel[1].substream);
	}
	return IRQ_HANDLED;
}