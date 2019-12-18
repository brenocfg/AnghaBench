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
struct snd_seq_timer {unsigned int tempo; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_seq_timer_set_tick_resolution (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_timer_set_tempo(struct snd_seq_timer * tmr, int tempo)
{
	unsigned long flags;

	if (snd_BUG_ON(!tmr))
		return -EINVAL;
	if (tempo <= 0)
		return -EINVAL;
	spin_lock_irqsave(&tmr->lock, flags);
	if ((unsigned int)tempo != tmr->tempo) {
		tmr->tempo = tempo;
		snd_seq_timer_set_tick_resolution(tmr);
	}
	spin_unlock_irqrestore(&tmr->lock, flags);
	return 0;
}