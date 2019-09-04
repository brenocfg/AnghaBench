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
struct fscache_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  lookup_jif; int /*<<< orphan*/  n_obj_ops; int /*<<< orphan*/  n_ops; int /*<<< orphan*/  debug_id; struct fscache_object* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOK_UP_OBJECT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_parent_ready(struct fscache_object *object,
							int event)
{
	struct fscache_object *parent = object->parent;

	_enter("{OBJ%x},%d", object->debug_id, event);

	ASSERT(parent != NULL);

	spin_lock(&parent->lock);
	parent->n_ops++;
	parent->n_obj_ops++;
	object->lookup_jif = jiffies;
	spin_unlock(&parent->lock);

	_leave("");
	return transit_to(LOOK_UP_OBJECT);
}