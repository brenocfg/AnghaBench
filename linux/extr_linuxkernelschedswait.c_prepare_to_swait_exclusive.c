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
struct swait_queue_head {int /*<<< orphan*/  lock; } ;
struct swait_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __prepare_to_swait (struct swait_queue_head*,struct swait_queue*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int) ; 

void prepare_to_swait_exclusive(struct swait_queue_head *q, struct swait_queue *wait, int state)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&q->lock, flags);
	__prepare_to_swait(q, wait);
	set_current_state(state);
	raw_spin_unlock_irqrestore(&q->lock, flags);
}