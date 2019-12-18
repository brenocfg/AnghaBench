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
struct worker_pool {int dummy; } ;
struct work_struct {int /*<<< orphan*/  data; } ;
struct pool_workqueue {struct worker_pool* pool; } ;

/* Variables and functions */
 int WORK_OFFQ_POOL_NONE ; 
 unsigned long WORK_OFFQ_POOL_SHIFT ; 
 unsigned long WORK_STRUCT_PWQ ; 
 unsigned long WORK_STRUCT_WQ_DATA_MASK ; 
 int /*<<< orphan*/  assert_rcu_or_pool_mutex () ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 struct worker_pool* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  worker_pool_idr ; 

__attribute__((used)) static struct worker_pool *get_work_pool(struct work_struct *work)
{
	unsigned long data = atomic_long_read(&work->data);
	int pool_id;

	assert_rcu_or_pool_mutex();

	if (data & WORK_STRUCT_PWQ)
		return ((struct pool_workqueue *)
			(data & WORK_STRUCT_WQ_DATA_MASK))->pool;

	pool_id = data >> WORK_OFFQ_POOL_SHIFT;
	if (pool_id == WORK_OFFQ_POOL_NONE)
		return NULL;

	return idr_find(&worker_pool_idr, pool_id);
}