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
struct snd_timer {int sticks; } ;
struct snd_azf3328 {int /*<<< orphan*/  reg_lock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_IO_TIMER_VALUE ; 
 unsigned int TIMER_COUNTDOWN_ENABLE ; 
 unsigned int TIMER_IRQ_ENABLE ; 
 int TIMER_VALUE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int seqtimer_scaling ; 
 int /*<<< orphan*/  snd_azf3328_ctrl_outl (struct snd_azf3328*,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_azf3328* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
snd_azf3328_timer_start(struct snd_timer *timer)
{
	struct snd_azf3328 *chip;
	unsigned long flags;
	unsigned int delay;

	chip = snd_timer_chip(timer);
	delay = ((timer->sticks * seqtimer_scaling) - 1) & TIMER_VALUE_MASK;
	if (delay < 49) {
		/* uhoh, that's not good, since user-space won't know about
		 * this timing tweak
		 * (we need to do it to avoid a lockup, though) */

		dev_dbg(chip->card->dev, "delay was too low (%d)!\n", delay);
		delay = 49; /* minimum time is 49 ticks */
	}
	dev_dbg(chip->card->dev, "setting timer countdown value %d\n", delay);
	delay |= TIMER_COUNTDOWN_ENABLE | TIMER_IRQ_ENABLE;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_azf3328_ctrl_outl(chip, IDX_IO_TIMER_VALUE, delay);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}