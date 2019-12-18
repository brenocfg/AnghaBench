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
struct snd_seq_timer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_timer_reset (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_timer_reset(struct snd_seq_timer *tmr)
{
	unsigned long flags;

	spin_lock_irqsave(&tmr->lock, flags);
	seq_timer_reset(tmr);
	spin_unlock_irqrestore(&tmr->lock, flags);
}