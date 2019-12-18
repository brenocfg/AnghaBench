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
typedef  size_t zend_long ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/ * elements; } ;
struct TYPE_5__ {TYPE_1__ array; } ;
typedef  TYPE_2__ spl_fixedarray_object ;

/* Variables and functions */
 scalar_t__ IS_LONG ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 size_t Z_LVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 size_t spl_offset_convert_to_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zval *spl_fixedarray_object_read_dimension_helper(spl_fixedarray_object *intern, zval *offset) /* {{{ */
{
	zend_long index;

	/* we have to return NULL on error here to avoid memleak because of
	 * ZE duplicating uninitialized_zval_ptr */
	if (!offset) {
		zend_throw_exception(spl_ce_RuntimeException, "Index invalid or out of range", 0);
		return NULL;
	}

	if (Z_TYPE_P(offset) != IS_LONG) {
		index = spl_offset_convert_to_long(offset);
	} else {
		index = Z_LVAL_P(offset);
	}

	if (index < 0 || index >= intern->array.size) {
		zend_throw_exception(spl_ce_RuntimeException, "Index invalid or out of range", 0);
		return NULL;
	} else if (Z_ISUNDEF(intern->array.elements[index])) {
		return NULL;
	} else {
		return &intern->array.elements[index];
	}
}