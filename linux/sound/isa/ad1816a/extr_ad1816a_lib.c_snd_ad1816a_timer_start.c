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
struct snd_timer {int sticks; } ;
struct snd_ad1816a {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  AD1816A_TIMER_BASE_COUNT ; 
 unsigned short AD1816A_TIMER_ENABLE ; 
 unsigned short snd_ad1816a_read (struct snd_ad1816a*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ad1816a_write (struct snd_ad1816a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ad1816a_write_mask (struct snd_ad1816a*,int /*<<< orphan*/ ,unsigned short,int) ; 
 struct snd_ad1816a* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ad1816a_timer_start(struct snd_timer *timer)
{
	unsigned short bits;
	unsigned long flags;
	struct snd_ad1816a *chip = snd_timer_chip(timer);
	spin_lock_irqsave(&chip->lock, flags);
	bits = snd_ad1816a_read(chip, AD1816A_INTERRUPT_ENABLE);

	if (!(bits & AD1816A_TIMER_ENABLE)) {
		snd_ad1816a_write(chip, AD1816A_TIMER_BASE_COUNT,
			timer->sticks & 0xffff);

		snd_ad1816a_write_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_TIMER_ENABLE, 0xffff);
	}
	spin_unlock_irqrestore(&chip->lock, flags);
	return 0;
}