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
 size_t spl_offset_convert_to_long (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int spl_fixedarray_object_has_dimension_helper(spl_fixedarray_object *intern, zval *offset, int check_empty) /* {{{ */
{
	zend_long index;
	int retval;

	if (Z_TYPE_P(offset) != IS_LONG) {
		index = spl_offset_convert_to_long(offset);
	} else {
		index = Z_LVAL_P(offset);
	}

	if (index < 0 || index >= intern->array.size) {
		retval = 0;
	} else {
		if (Z_ISUNDEF(intern->array.elements[index])) {
			retval = 0;
		} else if (check_empty) {
			if (zend_is_true(&intern->array.elements[index])) {
				retval = 1;
			} else {
				retval = 0;
			}
		} else { /* != NULL and !check_empty */
			retval = 1;
		}
	}

	return retval;
}