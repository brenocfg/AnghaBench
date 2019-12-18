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
struct viadev {unsigned int shadow_shift; unsigned char in_interrupt; scalar_t__ fragsize; scalar_t__ hwptr_done; scalar_t__ running; struct snd_pcm_substream* substream; } ;
struct via82xx {unsigned int num_devs; int /*<<< orphan*/  reg_lock; struct viadev* devs; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  OFFSET_STATUS ; 
 int /*<<< orphan*/  SGD_SHADOW ; 
 unsigned int VIA8233_SHADOW_STAT_ACTIVE ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAREG (struct via82xx*,int /*<<< orphan*/ ) ; 
 unsigned char VIA_REG_STAT_ACTIVE ; 
 unsigned int VIA_REG_STAT_EOL ; 
 unsigned int VIA_REG_STAT_FLAG ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_via8233_interrupt(int irq, void *dev_id)
{
	struct via82xx *chip = dev_id;
	unsigned int status;
	unsigned int i;
	int irqreturn = 0;

	/* check status for each stream */
	spin_lock(&chip->reg_lock);
	status = inl(VIAREG(chip, SGD_SHADOW));

	for (i = 0; i < chip->num_devs; i++) {
		struct viadev *viadev = &chip->devs[i];
		struct snd_pcm_substream *substream;
		unsigned char c_status, shadow_status;

		shadow_status = (status >> viadev->shadow_shift) &
			(VIA8233_SHADOW_STAT_ACTIVE|VIA_REG_STAT_EOL|
			 VIA_REG_STAT_FLAG);
		c_status = shadow_status & (VIA_REG_STAT_EOL|VIA_REG_STAT_FLAG);
		if (!c_status)
			continue;

		substream = viadev->substream;
		if (substream && viadev->running) {
			/*
			 * Update hwptr_done based on 'period elapsed'
			 * interrupts. We'll use it, when the chip returns 0 
			 * for OFFSET_CURR_COUNT.
			 */
			if (c_status & VIA_REG_STAT_EOL)
				viadev->hwptr_done = 0;
			else
				viadev->hwptr_done += viadev->fragsize;
			viadev->in_interrupt = c_status;
			if (shadow_status & VIA8233_SHADOW_STAT_ACTIVE)
				viadev->in_interrupt |= VIA_REG_STAT_ACTIVE;
			spin_unlock(&chip->reg_lock);

			snd_pcm_period_elapsed(substream);

			spin_lock(&chip->reg_lock);
			viadev->in_interrupt = 0;
		}
		outb(c_status, VIADEV_REG(viadev, OFFSET_STATUS)); /* ack */
		irqreturn = 1;
	}
	spin_unlock(&chip->reg_lock);
	return IRQ_RETVAL(irqreturn);
}