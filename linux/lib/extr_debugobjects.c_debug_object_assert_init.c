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
struct debug_obj_descr {int /*<<< orphan*/  fixup_assert_init; scalar_t__ (* is_static_object ) (void*) ;} ;
struct debug_obj {void* object; struct debug_obj_descr* descr; int /*<<< orphan*/  state; } ;
struct debug_bucket {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODEBUG_STATE_NOTAVAILABLE ; 
 int /*<<< orphan*/  debug_object_fixup (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_object_init (void*,struct debug_obj_descr*) ; 
 int /*<<< orphan*/  debug_objects_enabled ; 
 int /*<<< orphan*/  debug_print_object (struct debug_obj*,char*) ; 
 struct debug_bucket* get_bucket (unsigned long) ; 
 struct debug_obj* lookup_object (void*,struct debug_bucket*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (void*) ; 

void debug_object_assert_init(void *addr, struct debug_obj_descr *descr)
{
	struct debug_bucket *db;
	struct debug_obj *obj;
	unsigned long flags;

	if (!debug_objects_enabled)
		return;

	db = get_bucket((unsigned long) addr);

	raw_spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	if (!obj) {
		struct debug_obj o = { .object = addr,
				       .state = ODEBUG_STATE_NOTAVAILABLE,
				       .descr = descr };

		raw_spin_unlock_irqrestore(&db->lock, flags);
		/*
		 * Maybe the object is static, and we let the type specific
		 * code confirm. Track this static object if true, else invoke
		 * fixup.
		 */
		if (descr->is_static_object && descr->is_static_object(addr)) {
			/* Track this static object */
			debug_object_init(addr, descr);
		} else {
			debug_print_object(&o, "assert_init");
			debug_object_fixup(descr->fixup_assert_init, addr,
					   ODEBUG_STATE_NOTAVAILABLE);
		}
		return;
	}

	raw_spin_unlock_irqrestore(&db->lock, flags);
}