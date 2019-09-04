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
struct snd_timer {int dummy; } ;
struct snd_azf3328 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 scalar_t__ IDX_IO_TIMER_VALUE ; 
 int /*<<< orphan*/  snd_azf3328_ctrl_outb (struct snd_azf3328*,scalar_t__,int) ; 
 struct snd_azf3328* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
snd_azf3328_timer_stop(struct snd_timer *timer)
{
	struct snd_azf3328 *chip;
	unsigned long flags;

	chip = snd_timer_chip(timer);
	spin_lock_irqsave(&chip->reg_lock, flags);
	/* disable timer countdown and interrupt */
	/* Hmm, should we write TIMER_IRQ_ACK here?
	   YES indeed, otherwise a rogue timer operation - which prompts
	   ALSA(?) to call repeated stop() in vain, but NOT start() -
	   will never end (value 0x03 is kept shown in control byte).
	   Simply manually poking 0x04 _once_ immediately successfully stops
	   the hardware/ALSA interrupt activity. */
	snd_azf3328_ctrl_outb(chip, IDX_IO_TIMER_VALUE + 3, 0x04);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}