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
struct fscache_state {int dummy; } ;
struct fscache_object {scalar_t__ n_ops; scalar_t__ n_children; scalar_t__ n_in_progress; int /*<<< orphan*/  dependents; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; scalar_t__ oob_event_mask; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_OBJECT ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_PENDING_WRITE ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_RETIRED ; 
 int /*<<< orphan*/  KILL_DEPENDENTS ; 
 int /*<<< orphan*/  WAIT_FOR_CLEARANCE ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_cancel_all_ops (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_mark_object_dead (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_start_operations (struct fscache_object*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_kill_object(struct fscache_object *object,
						       int event)
{
	_enter("{OBJ%x,%d,%d},%d",
	       object->debug_id, object->n_ops, object->n_children, event);

	fscache_mark_object_dead(object);
	object->oob_event_mask = 0;

	if (test_bit(FSCACHE_OBJECT_RETIRED, &object->flags)) {
		/* Reject any new read/write ops and abort any that are pending. */
		clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
		fscache_cancel_all_ops(object);
	}

	if (list_empty(&object->dependents) &&
	    object->n_ops == 0 &&
	    object->n_children == 0)
		return transit_to(DROP_OBJECT);

	if (object->n_in_progress == 0) {
		spin_lock(&object->lock);
		if (object->n_ops > 0 && object->n_in_progress == 0)
			fscache_start_operations(object);
		spin_unlock(&object->lock);
	}

	if (!list_empty(&object->dependents))
		return transit_to(KILL_DEPENDENTS);

	return transit_to(WAIT_FOR_CLEARANCE);
}