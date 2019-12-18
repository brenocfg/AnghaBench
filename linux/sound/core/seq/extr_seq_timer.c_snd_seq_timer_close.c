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
struct snd_timer_instance {int dummy; } ;
struct snd_seq_timer {int /*<<< orphan*/  lock; struct snd_timer_instance* timeri; } ;
struct snd_seq_queue {struct snd_seq_timer* timer; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_timer_close (struct snd_timer_instance*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_seq_timer_close(struct snd_seq_queue *q)
{
	struct snd_seq_timer *tmr;
	struct snd_timer_instance *t;
	
	tmr = q->timer;
	if (snd_BUG_ON(!tmr))
		return -EINVAL;
	spin_lock_irq(&tmr->lock);
	t = tmr->timeri;
	tmr->timeri = NULL;
	spin_unlock_irq(&tmr->lock);
	if (t)
		snd_timer_close(t);
	return 0;
}