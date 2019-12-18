#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_7__ {int row_num; TYPE_1__ intern; int /*<<< orphan*/  result; } ;
typedef  TYPE_2__ php_mysqli_result_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_MYSQLI_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* ecalloc (int,int) ; 
 int /*<<< orphan*/  php_mysqli_result_iterator_funcs ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_iterator_init (TYPE_1__*) ; 

zend_object_iterator *php_mysqli_result_get_iterator(zend_class_entry *ce, zval *object, int by_ref)
{
	php_mysqli_result_iterator *iterator;

	if (by_ref) {
		zend_error(E_ERROR, "An iterator cannot be used with foreach by reference");
	}
	iterator = ecalloc(1, sizeof(php_mysqli_result_iterator));
	zend_iterator_init(&iterator->intern);

	Z_ADDREF_P(object);
	ZVAL_OBJ(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &php_mysqli_result_iterator_funcs;
	iterator->result = Z_MYSQLI_P(object);
	iterator->row_num = -1;

	return &iterator->intern;
}