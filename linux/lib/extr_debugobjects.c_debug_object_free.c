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
struct debug_obj_descr {int /*<<< orphan*/  fixup_free; } ;
struct debug_obj {int state; int /*<<< orphan*/  node; } ;
struct debug_bucket {int /*<<< orphan*/  lock; } ;
typedef  enum debug_obj_state { ____Placeholder_debug_obj_state } debug_obj_state ;

/* Variables and functions */
#define  ODEBUG_STATE_ACTIVE 128 
 int /*<<< orphan*/  debug_object_fixup (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  debug_objects_enabled ; 
 int /*<<< orphan*/  debug_print_object (struct debug_obj*,char*) ; 
 int /*<<< orphan*/  free_object (struct debug_obj*) ; 
 struct debug_bucket* get_bucket (unsigned long) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 struct debug_obj* lookup_object (void*,struct debug_bucket*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void debug_object_free(void *addr, struct debug_obj_descr *descr)
{
	enum debug_obj_state state;
	struct debug_bucket *db;
	struct debug_obj *obj;
	unsigned long flags;

	if (!debug_objects_enabled)
		return;

	db = get_bucket((unsigned long) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	if (!obj)
		goto out_unlock;

	switch (obj->state) {
	case ODEBUG_STATE_ACTIVE:
		state = obj->state;
		raw_spin_unlock_irqrestore(&db->lock, flags);
		debug_print_object(obj, "free");
		debug_object_fixup(descr->fixup_free, addr, state);
		return;
	default:
		hlist_del(&obj->node);
		raw_spin_unlock_irqrestore(&db->lock, flags);
		free_object(obj);
		return;
	}
out_unlock:
	raw_spin_unlock_irqrestore(&db->lock, flags);
}