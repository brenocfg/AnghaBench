#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zend_object_iterator ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_9__ {int flags; scalar_t__ current; TYPE_1__ array; } ;
typedef  TYPE_3__ spl_fixedarray_object ;

/* Variables and functions */
 int FAILURE ; 
 int SPL_FIXEDARRAY_OVERLOADED_VALID ; 
 int SUCCESS ; 
 TYPE_3__* Z_SPLFIXEDARRAY_P (int /*<<< orphan*/ *) ; 
 int zend_user_it_valid (TYPE_2__*) ; 

__attribute__((used)) static int spl_fixedarray_it_valid(zend_object_iterator *iter) /* {{{ */
{
	spl_fixedarray_object *object = Z_SPLFIXEDARRAY_P(&iter->data);

	if (object->flags & SPL_FIXEDARRAY_OVERLOADED_VALID) {
		return zend_user_it_valid(iter);
	}

	if (object->current >= 0 && object->current < object->array.size) {
		return SUCCESS;
	}

	return FAILURE;
}