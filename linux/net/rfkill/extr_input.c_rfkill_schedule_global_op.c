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
typedef  enum rfkill_sched_op { ____Placeholder_rfkill_sched_op } rfkill_sched_op ;

/* Variables and functions */
 int RFKILL_GLOBAL_OP_EPO ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_is_epo_lock_active () ; 
 int /*<<< orphan*/  rfkill_last_scheduled ; 
 int rfkill_op ; 
 int /*<<< orphan*/  rfkill_op_lock ; 
 int rfkill_op_pending ; 
 int /*<<< orphan*/  rfkill_op_work ; 
 int /*<<< orphan*/  rfkill_schedule_ratelimited () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void rfkill_schedule_global_op(enum rfkill_sched_op op)
{
	unsigned long flags;

	spin_lock_irqsave(&rfkill_op_lock, flags);
	rfkill_op = op;
	rfkill_op_pending = true;
	if (op == RFKILL_GLOBAL_OP_EPO && !rfkill_is_epo_lock_active()) {
		/* bypass the limiter for EPO */
		mod_delayed_work(system_wq, &rfkill_op_work, 0);
		rfkill_last_scheduled = jiffies;
	} else
		rfkill_schedule_ratelimited();
	spin_unlock_irqrestore(&rfkill_op_lock, flags);
}