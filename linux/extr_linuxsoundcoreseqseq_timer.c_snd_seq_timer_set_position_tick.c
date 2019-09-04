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
struct TYPE_2__ {scalar_t__ fraction; int /*<<< orphan*/  cur_tick; } ;
struct snd_seq_timer {int /*<<< orphan*/  lock; TYPE_1__ tick; } ;
typedef  int /*<<< orphan*/  snd_seq_tick_time_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_timer_set_position_tick(struct snd_seq_timer *tmr,
				    snd_seq_tick_time_t position)
{
	unsigned long flags;

	if (snd_BUG_ON(!tmr))
		return -EINVAL;

	spin_lock_irqsave(&tmr->lock, flags);
	tmr->tick.cur_tick = position;
	tmr->tick.fraction = 0;
	spin_unlock_irqrestore(&tmr->lock, flags);
	return 0;
}