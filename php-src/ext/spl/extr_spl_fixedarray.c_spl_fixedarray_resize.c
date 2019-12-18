#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  size_t zend_long ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ spl_fixedarray ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * erealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/ * safe_erealloc (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_fixedarray_init (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_fixedarray_resize(spl_fixedarray *array, zend_long size) /* {{{ */
{
	if (size == array->size) {
		/* nothing to do */
		return;
	}

	/* first initialization */
	if (array->size == 0) {
		spl_fixedarray_init(array, size);
		return;
	}

	/* clearing the array */
	if (size == 0) {
		zend_long i;

		for (i = 0; i < array->size; i++) {
			zval_ptr_dtor(&(array->elements[i]));
		}

		if (array->elements) {
			efree(array->elements);
			array->elements = NULL;
		}
	} else if (size > array->size) {
		array->elements = safe_erealloc(array->elements, size, sizeof(zval), 0);
		memset(array->elements + array->size, '\0', sizeof(zval) * (size - array->size));
	} else { /* size < array->size */
		zend_long i;

		for (i = size; i < array->size; i++) {
			zval_ptr_dtor(&(array->elements[i]));
		}
		array->elements = erealloc(array->elements, sizeof(zval) * size);
	}

	array->size = size;
}