#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_opl3sa2 {TYPE_3__* master_volume; TYPE_2__* master_switch; int /*<<< orphan*/  wss; TYPE_1__* rmidi; int /*<<< orphan*/  synth; } ;
struct snd_card {struct snd_opl3sa2* private_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  OPL3SA2_IRQ_STATUS ; 
 int /*<<< orphan*/  OPL3SA2_MASTER_LEFT ; 
 int /*<<< orphan*/  OPL3SA2_MASTER_RIGHT ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl3_interrupt (int /*<<< orphan*/ ) ; 
 unsigned short snd_opl3sa2_read (struct snd_opl3sa2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_wss_interrupt (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snd_opl3sa2_interrupt(int irq, void *dev_id)
{
	unsigned short status;
	struct snd_card *card = dev_id;
	struct snd_opl3sa2 *chip;
	int handled = 0;

	if (card == NULL)
		return IRQ_NONE;

	chip = card->private_data;
	status = snd_opl3sa2_read(chip, OPL3SA2_IRQ_STATUS);

	if (status & 0x20) {
		handled = 1;
		snd_opl3_interrupt(chip->synth);
	}

	if ((status & 0x10) && chip->rmidi != NULL) {
		handled = 1;
		snd_mpu401_uart_interrupt(irq, chip->rmidi->private_data);
	}

	if (status & 0x07) {	/* TI,CI,PI */
		handled = 1;
		snd_wss_interrupt(irq, chip->wss);
	}

	if (status & 0x40) { /* hardware volume change */
		handled = 1;
		/* reading from Master Lch register at 0x07 clears this bit */
		snd_opl3sa2_read(chip, OPL3SA2_MASTER_RIGHT);
		snd_opl3sa2_read(chip, OPL3SA2_MASTER_LEFT);
		if (chip->master_switch && chip->master_volume) {
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_switch->id);
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_volume->id);
		}
	}
	return IRQ_RETVAL(handled);
}