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
struct snd_timer_instance {struct snd_timer* timer; } ;
struct snd_timer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long snd_timer_hw_resolution (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long snd_timer_resolution(struct snd_timer_instance *timeri)
{
	struct snd_timer * timer;
	unsigned long ret = 0;
	unsigned long flags;

	if (timeri == NULL)
		return 0;
	timer = timeri->timer;
	if (timer) {
		spin_lock_irqsave(&timer->lock, flags);
		ret = snd_timer_hw_resolution(timer);
		spin_unlock_irqrestore(&timer->lock, flags);
	}
	return ret;
}