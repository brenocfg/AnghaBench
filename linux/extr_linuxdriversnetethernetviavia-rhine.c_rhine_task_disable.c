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
struct rhine_private {int task_enable; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  slow_event_task; int /*<<< orphan*/  task_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rhine_task_disable(struct rhine_private *rp)
{
	mutex_lock(&rp->task_lock);
	rp->task_enable = false;
	mutex_unlock(&rp->task_lock);

	cancel_work_sync(&rp->slow_event_task);
	cancel_work_sync(&rp->reset_task);
}