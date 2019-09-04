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
struct work_struct {int dummy; } ;
struct pool_workqueue {int /*<<< orphan*/  nr_active; TYPE_1__* pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  worklist; int /*<<< orphan*/  watchdog_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_STRUCT_DELAYED_BIT ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pool_workqueue* get_work_pwq (struct work_struct*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_linked_works (struct work_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_workqueue_activate_work (struct work_struct*) ; 
 int /*<<< orphan*/  work_data_bits (struct work_struct*) ; 

__attribute__((used)) static void pwq_activate_delayed_work(struct work_struct *work)
{
	struct pool_workqueue *pwq = get_work_pwq(work);

	trace_workqueue_activate_work(work);
	if (list_empty(&pwq->pool->worklist))
		pwq->pool->watchdog_ts = jiffies;
	move_linked_works(work, &pwq->pool->worklist, NULL);
	__clear_bit(WORK_STRUCT_DELAYED_BIT, work_data_bits(work));
	pwq->nr_active++;
}