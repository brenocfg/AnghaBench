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
struct debug_percpu_free {scalar_t__ obj_free; int /*<<< orphan*/  free_objs; } ;
struct debug_obj {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int ODEBUG_BATCH_SIZE ; 
 scalar_t__ ODEBUG_FREE_WORK_MAX ; 
 scalar_t__ ODEBUG_POOL_PERCPU_SIZE ; 
 struct debug_obj* __alloc_object (int /*<<< orphan*/ *) ; 
 scalar_t__ debug_objects_pool_size ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ obj_cache ; 
 scalar_t__ obj_nr_tofree ; 
 int /*<<< orphan*/  obj_pool ; 
 scalar_t__ obj_pool_free ; 
 scalar_t__ obj_pool_used ; 
 int /*<<< orphan*/  obj_to_free ; 
 int /*<<< orphan*/  percpu_obj_pool ; 
 int /*<<< orphan*/  pool_lock ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 struct debug_percpu_free* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __free_object(struct debug_obj *obj)
{
	struct debug_obj *objs[ODEBUG_BATCH_SIZE];
	struct debug_percpu_free *percpu_pool;
	int lookahead_count = 0;
	unsigned long flags;
	bool work;

	local_irq_save(flags);
	if (!obj_cache)
		goto free_to_obj_pool;

	/*
	 * Try to free it into the percpu pool first.
	 */
	percpu_pool = this_cpu_ptr(&percpu_obj_pool);
	if (percpu_pool->obj_free < ODEBUG_POOL_PERCPU_SIZE) {
		hlist_add_head(&obj->node, &percpu_pool->free_objs);
		percpu_pool->obj_free++;
		local_irq_restore(flags);
		return;
	}

	/*
	 * As the percpu pool is full, look ahead and pull out a batch
	 * of objects from the percpu pool and free them as well.
	 */
	for (; lookahead_count < ODEBUG_BATCH_SIZE; lookahead_count++) {
		objs[lookahead_count] = __alloc_object(&percpu_pool->free_objs);
		if (!objs[lookahead_count])
			break;
		percpu_pool->obj_free--;
	}

free_to_obj_pool:
	raw_spin_lock(&pool_lock);
	work = (obj_pool_free > debug_objects_pool_size) && obj_cache &&
	       (obj_nr_tofree < ODEBUG_FREE_WORK_MAX);
	obj_pool_used--;

	if (work) {
		obj_nr_tofree++;
		hlist_add_head(&obj->node, &obj_to_free);
		if (lookahead_count) {
			obj_nr_tofree += lookahead_count;
			obj_pool_used -= lookahead_count;
			while (lookahead_count) {
				hlist_add_head(&objs[--lookahead_count]->node,
					       &obj_to_free);
			}
		}

		if ((obj_pool_free > debug_objects_pool_size) &&
		    (obj_nr_tofree < ODEBUG_FREE_WORK_MAX)) {
			int i;

			/*
			 * Free one more batch of objects from obj_pool.
			 */
			for (i = 0; i < ODEBUG_BATCH_SIZE; i++) {
				obj = __alloc_object(&obj_pool);
				hlist_add_head(&obj->node, &obj_to_free);
				obj_pool_free--;
				obj_nr_tofree++;
			}
		}
	} else {
		obj_pool_free++;
		hlist_add_head(&obj->node, &obj_pool);
		if (lookahead_count) {
			obj_pool_free += lookahead_count;
			obj_pool_used -= lookahead_count;
			while (lookahead_count) {
				hlist_add_head(&objs[--lookahead_count]->node,
					       &obj_pool);
			}
		}
	}
	raw_spin_unlock(&pool_lock);
	local_irq_restore(flags);
}