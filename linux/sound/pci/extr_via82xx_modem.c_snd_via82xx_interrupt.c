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
struct viadev {scalar_t__ substream; scalar_t__ running; } ;
struct via82xx_modem {unsigned int intr_mask; unsigned int num_devs; int /*<<< orphan*/  reg_lock; struct viadev* devs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OFFSET_STATUS ; 
 int /*<<< orphan*/  SGD_SHADOW ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAREG (struct via82xx_modem*,int /*<<< orphan*/ ) ; 
 unsigned char VIA_REG_STAT_EOL ; 
 unsigned char VIA_REG_STAT_FLAG ; 
 unsigned char VIA_REG_STAT_STOPPED ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_via82xx_interrupt(int irq, void *dev_id)
{
	struct via82xx_modem *chip = dev_id;
	unsigned int status;
	unsigned int i;

	status = inl(VIAREG(chip, SGD_SHADOW));
	if (! (status & chip->intr_mask)) {
		return IRQ_NONE;
	}
// _skip_sgd:

	/* check status for each stream */
	spin_lock(&chip->reg_lock);
	for (i = 0; i < chip->num_devs; i++) {
		struct viadev *viadev = &chip->devs[i];
		unsigned char c_status = inb(VIADEV_REG(viadev, OFFSET_STATUS));
		c_status &= (VIA_REG_STAT_EOL|VIA_REG_STAT_FLAG|VIA_REG_STAT_STOPPED);
		if (! c_status)
			continue;
		if (viadev->substream && viadev->running) {
			spin_unlock(&chip->reg_lock);
			snd_pcm_period_elapsed(viadev->substream);
			spin_lock(&chip->reg_lock);
		}
		outb(c_status, VIADEV_REG(viadev, OFFSET_STATUS)); /* ack */
	}
	spin_unlock(&chip->reg_lock);
	return IRQ_HANDLED;
}