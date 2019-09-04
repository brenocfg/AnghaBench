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
struct mwifiex_adapter {int more_task_flag; int /*<<< orphan*/  main_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  main_proc_lock; scalar_t__ mwifiex_processing; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mwifiex_queue_main_work(struct mwifiex_adapter *adapter)
{
	unsigned long flags;

	spin_lock_irqsave(&adapter->main_proc_lock, flags);
	if (adapter->mwifiex_processing) {
		adapter->more_task_flag = true;
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
	} else {
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
		queue_work(adapter->workqueue, &adapter->main_work);
	}
}