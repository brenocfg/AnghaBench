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
struct mwifiex_adapter {int /*<<< orphan*/  cmd_pending_q_lock; int /*<<< orphan*/  cmd_pending_q; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int is_command_pending(struct mwifiex_adapter *adapter)
{
	unsigned long flags;
	int is_cmd_pend_q_empty;

	spin_lock_irqsave(&adapter->cmd_pending_q_lock, flags);
	is_cmd_pend_q_empty = list_empty(&adapter->cmd_pending_q);
	spin_unlock_irqrestore(&adapter->cmd_pending_q_lock, flags);

	return !is_cmd_pend_q_empty;
}