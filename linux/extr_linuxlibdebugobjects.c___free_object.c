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
struct debug_obj {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ debug_objects_pool_size ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ obj_cache ; 
 int /*<<< orphan*/  obj_nr_tofree ; 
 int /*<<< orphan*/  obj_pool ; 
 scalar_t__ obj_pool_free ; 
 int /*<<< orphan*/  obj_pool_used ; 
 int /*<<< orphan*/  obj_to_free ; 
 int /*<<< orphan*/  pool_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool __free_object(struct debug_obj *obj)
{
	unsigned long flags;
	bool work;

	raw_spin_lock_irqsave(&pool_lock, flags);
	work = (obj_pool_free > debug_objects_pool_size) && obj_cache;
	obj_pool_used--;

	if (work) {
		obj_nr_tofree++;
		hlist_add_head(&obj->node, &obj_to_free);
	} else {
		obj_pool_free++;
		hlist_add_head(&obj->node, &obj_pool);
	}
	raw_spin_unlock_irqrestore(&pool_lock, flags);
	return work;
}