#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int max_txq_num; } ;
struct il_priv {int cmd_queue; int /*<<< orphan*/  watchdog; TYPE_1__ hw_params; TYPE_2__* cfg; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {unsigned long wd_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_WD_TICK (unsigned long) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 struct il_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct il_priv* il ; 
 scalar_t__ il_check_stuck_queue (struct il_priv*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog ; 

void
il_bg_watchdog(struct timer_list *t)
{
	struct il_priv *il = from_timer(il, t, watchdog);
	int cnt;
	unsigned long timeout;

	if (test_bit(S_EXIT_PENDING, &il->status))
		return;

	timeout = il->cfg->wd_timeout;
	if (timeout == 0)
		return;

	/* monitor and check for stuck cmd queue */
	if (il_check_stuck_queue(il, il->cmd_queue))
		return;

	/* monitor and check for other stuck queues */
	for (cnt = 0; cnt < il->hw_params.max_txq_num; cnt++) {
		/* skip as we already checked the command queue */
		if (cnt == il->cmd_queue)
			continue;
		if (il_check_stuck_queue(il, cnt))
			return;
	}

	mod_timer(&il->watchdog,
		  jiffies + msecs_to_jiffies(IL_WD_TICK(timeout)));
}