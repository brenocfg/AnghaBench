#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {TYPE_2__* funcs; } ;
typedef  TYPE_3__ zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_error_handling ;
struct TYPE_10__ {size_t level; TYPE_1__* iterators; } ;
typedef  TYPE_4__ spl_recursive_it_object ;
struct TYPE_8__ {int /*<<< orphan*/ * (* get_current_data ) (TYPE_3__*) ;} ;
struct TYPE_7__ {TYPE_3__* iterator; } ;

/* Variables and functions */
 int /*<<< orphan*/  EH_THROW ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ce_UnexpectedValueException ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_replace_error_handling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_restore_error_handling (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_recursive_tree_iterator_get_entry(spl_recursive_it_object *object, zval *return_value)
{
	zend_object_iterator      *iterator = object->iterators[object->level].iterator;
	zval                      *data;
	zend_error_handling        error_handling;

	data = iterator->funcs->get_current_data(iterator);

	/* Replace exception handling so the catchable fatal error that is thrown when a class
	 * without __toString is converted to string is converted into an exception. */
	zend_replace_error_handling(EH_THROW, spl_ce_UnexpectedValueException, &error_handling);
	if (data) {
		ZVAL_DEREF(data);
		if (Z_TYPE_P(data) == IS_ARRAY) {
			ZVAL_STRINGL(return_value, "Array", sizeof("Array")-1);
		} else {
			ZVAL_COPY(return_value, data);
			convert_to_string(return_value);
		}
	}
	zend_restore_error_handling(&error_handling);
}