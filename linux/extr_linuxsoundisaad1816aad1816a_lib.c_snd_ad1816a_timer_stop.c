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
struct snd_ad1816a {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  AD1816A_TIMER_ENABLE ; 
 int /*<<< orphan*/  snd_ad1816a_write_mask (struct snd_ad1816a*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_ad1816a* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ad1816a_timer_stop(struct snd_timer *timer)
{
	unsigned long flags;
	struct snd_ad1816a *chip = snd_timer_chip(timer);
	spin_lock_irqsave(&chip->lock, flags);

	snd_ad1816a_write_mask(chip, AD1816A_INTERRUPT_ENABLE,
		AD1816A_TIMER_ENABLE, 0x0000);

	spin_unlock_irqrestore(&chip->lock, flags);
	return 0;
}