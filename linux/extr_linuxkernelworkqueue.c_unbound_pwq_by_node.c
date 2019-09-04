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
struct workqueue_struct {int /*<<< orphan*/ * numa_pwq_tbl; struct pool_workqueue* dfl_pwq; } ;
struct pool_workqueue {int dummy; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  assert_rcu_or_wq_mutex_or_pool_mutex (struct workqueue_struct*) ; 
 struct pool_workqueue* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct pool_workqueue *unbound_pwq_by_node(struct workqueue_struct *wq,
						  int node)
{
	assert_rcu_or_wq_mutex_or_pool_mutex(wq);

	/*
	 * XXX: @node can be NUMA_NO_NODE if CPU goes offline while a
	 * delayed item is pending.  The plan is to keep CPU -> NODE
	 * mapping valid and stable across CPU on/offlines.  Once that
	 * happens, this workaround can be removed.
	 */
	if (unlikely(node == NUMA_NO_NODE))
		return wq->dfl_pwq;

	return rcu_dereference_raw(wq->numa_pwq_tbl[node]);
}