#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  current; } ;
typedef  TYPE_2__ spl_fixedarray_object ;

/* Variables and functions */
 int SPL_FIXEDARRAY_OVERLOADED_NEXT ; 
 TYPE_2__* Z_SPLFIXEDARRAY_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_user_it_invalidate_current (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_user_it_move_forward (TYPE_1__*) ; 

__attribute__((used)) static void spl_fixedarray_it_move_forward(zend_object_iterator *iter) /* {{{ */
{
	spl_fixedarray_object *object = Z_SPLFIXEDARRAY_P(&iter->data);

	if (object->flags & SPL_FIXEDARRAY_OVERLOADED_NEXT) {
		zend_user_it_move_forward(iter);
	} else {
		zend_user_it_invalidate_current(iter);
		object->current++;
	}
}