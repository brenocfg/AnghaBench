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
struct workqueue_struct {int flags; } ;
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WORK_STRUCT_PENDING_BIT ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  __queue_work (int,struct workqueue_struct*,struct work_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_data_bits (struct work_struct*) ; 
 int workqueue_select_cpu_near (int) ; 

bool queue_work_node(int node, struct workqueue_struct *wq,
		     struct work_struct *work)
{
	unsigned long flags;
	bool ret = false;

	/*
	 * This current implementation is specific to unbound workqueues.
	 * Specifically we only return the first available CPU for a given
	 * node instead of cycling through individual CPUs within the node.
	 *
	 * If this is used with a per-cpu workqueue then the logic in
	 * workqueue_select_cpu_near would need to be updated to allow for
	 * some round robin type logic.
	 */
	WARN_ON_ONCE(!(wq->flags & WQ_UNBOUND));

	local_irq_save(flags);

	if (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work))) {
		int cpu = workqueue_select_cpu_near(node);

		__queue_work(cpu, wq, work);
		ret = true;
	}

	local_irq_restore(flags);
	return ret;
}