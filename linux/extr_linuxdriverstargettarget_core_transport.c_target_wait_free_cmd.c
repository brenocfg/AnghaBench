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
struct se_cmd {int /*<<< orphan*/  t_state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __transport_wait_for_tasks (struct se_cmd*,int,int*,int*,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void target_wait_free_cmd(struct se_cmd *cmd, bool *aborted, bool *tas)
{
	unsigned long flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	__transport_wait_for_tasks(cmd, true, aborted, tas, &flags);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);
}