#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  ce; } ;
struct TYPE_5__ {int /*<<< orphan*/  heap; scalar_t__ fptr_count; TYPE_1__ std; } ;
typedef  TYPE_2__ spl_heap_object ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 TYPE_2__* spl_heap_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ptr_heap_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_call_method_with_0_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_heap_object_count_elements(zend_object *object, zend_long *count) /* {{{ */
{
	spl_heap_object *intern = spl_heap_from_obj(object);

	if (intern->fptr_count) {
		zval rv;
		zend_call_method_with_0_params(object, intern->std.ce, &intern->fptr_count, "count", &rv);
		if (!Z_ISUNDEF(rv)) {
			*count = zval_get_long(&rv);
			zval_ptr_dtor(&rv);
			return SUCCESS;
		}
		*count = 0;
		return FAILURE;
	}

	*count = spl_ptr_heap_count(intern->heap);

	return SUCCESS;
}