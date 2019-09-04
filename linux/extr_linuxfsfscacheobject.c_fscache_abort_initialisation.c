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
struct fscache_object {scalar_t__ oob_event_mask; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KILL_OBJECT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fscache_dequeue_object (struct fscache_object*) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_abort_initialisation(struct fscache_object *object,
								int event)
{
	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_event_mask = 0;
	fscache_dequeue_object(object);
	return transit_to(KILL_OBJECT);
}