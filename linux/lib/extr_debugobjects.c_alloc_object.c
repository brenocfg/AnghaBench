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
struct debug_percpu_free {int /*<<< orphan*/  obj_free; int /*<<< orphan*/  free_objs; } ;
struct debug_obj_descr {int dummy; } ;
struct debug_obj {int /*<<< orphan*/  node; scalar_t__ astate; int /*<<< orphan*/  state; struct debug_obj_descr* descr; void* object; } ;
struct debug_bucket {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ODEBUG_BATCH_SIZE ; 
 int /*<<< orphan*/  ODEBUG_STATE_NONE ; 
 struct debug_obj* __alloc_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_cache ; 
 int /*<<< orphan*/  obj_pool ; 
 scalar_t__ obj_pool_free ; 
 scalar_t__ obj_pool_max_used ; 
 scalar_t__ obj_pool_min_free ; 
 scalar_t__ obj_pool_used ; 
 int /*<<< orphan*/  percpu_obj_pool ; 
 int /*<<< orphan*/  pool_lock ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 struct debug_percpu_free* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct debug_obj *
alloc_object(void *addr, struct debug_bucket *b, struct debug_obj_descr *descr)
{
	struct debug_percpu_free *percpu_pool = this_cpu_ptr(&percpu_obj_pool);
	struct debug_obj *obj;

	if (likely(obj_cache)) {
		obj = __alloc_object(&percpu_pool->free_objs);
		if (obj) {
			percpu_pool->obj_free--;
			goto init_obj;
		}
	}

	raw_spin_lock(&pool_lock);
	obj = __alloc_object(&obj_pool);
	if (obj) {
		obj_pool_used++;
		obj_pool_free--;

		/*
		 * Looking ahead, allocate one batch of debug objects and
		 * put them into the percpu free pool.
		 */
		if (likely(obj_cache)) {
			int i;

			for (i = 0; i < ODEBUG_BATCH_SIZE; i++) {
				struct debug_obj *obj2;

				obj2 = __alloc_object(&obj_pool);
				if (!obj2)
					break;
				hlist_add_head(&obj2->node,
					       &percpu_pool->free_objs);
				percpu_pool->obj_free++;
				obj_pool_used++;
				obj_pool_free--;
			}
		}

		if (obj_pool_used > obj_pool_max_used)
			obj_pool_max_used = obj_pool_used;

		if (obj_pool_free < obj_pool_min_free)
			obj_pool_min_free = obj_pool_free;
	}
	raw_spin_unlock(&pool_lock);

init_obj:
	if (obj) {
		obj->object = addr;
		obj->descr  = descr;
		obj->state  = ODEBUG_STATE_NONE;
		obj->astate = 0;
		hlist_add_head(&obj->node, &b->list);
	}
	return obj;
}