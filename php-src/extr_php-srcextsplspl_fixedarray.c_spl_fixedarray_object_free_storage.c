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
typedef  int /*<<< orphan*/  zend_object ;
typedef  size_t zend_long ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * elements; } ;
struct TYPE_5__ {int /*<<< orphan*/  std; TYPE_1__ array; } ;
typedef  TYPE_2__ spl_fixedarray_object ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 TYPE_2__* spl_fixed_array_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_fixedarray_object_free_storage(zend_object *object) /* {{{ */
{
	spl_fixedarray_object *intern = spl_fixed_array_from_obj(object);
	zend_long i;

	if (intern->array.size > 0) {
		for (i = 0; i < intern->array.size; i++) {
			zval_ptr_dtor(&(intern->array.elements[i]));
		}

		if (intern->array.size > 0 && intern->array.elements) {
			efree(intern->array.elements);
		}
	}

	zend_object_std_dtor(&intern->std);
}