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
struct fscache_object {int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_OBJECT_EV_ERROR ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_raise_event (struct fscache_object*,int /*<<< orphan*/ ) ; 

void fscache_abort_object(struct fscache_object *object)
{
	_enter("{OBJ%x}", object->debug_id);

	fscache_raise_event(object, FSCACHE_OBJECT_EV_ERROR);
}