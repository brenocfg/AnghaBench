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
struct snd_timer {int /*<<< orphan*/  lock; int /*<<< orphan*/  sack_list_head; TYPE_1__* card; } ;
struct TYPE_2__ {scalar_t__ shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_timer_clear_callbacks (struct snd_timer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_timer_process_callbacks (struct snd_timer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_timer_tasklet(unsigned long arg)
{
	struct snd_timer *timer = (struct snd_timer *) arg;
	unsigned long flags;

	if (timer->card && timer->card->shutdown) {
		snd_timer_clear_callbacks(timer, &timer->sack_list_head);
		return;
	}

	spin_lock_irqsave(&timer->lock, flags);
	snd_timer_process_callbacks(timer, &timer->sack_list_head);
	spin_unlock_irqrestore(&timer->lock, flags);
}