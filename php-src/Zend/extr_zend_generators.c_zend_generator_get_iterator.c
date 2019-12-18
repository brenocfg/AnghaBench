#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_12__ {int /*<<< orphan*/  data; int /*<<< orphan*/ * funcs; } ;
typedef  TYPE_4__ zend_object_iterator ;
struct TYPE_13__ {TYPE_4__* iterator; TYPE_3__* execute_data; } ;
typedef  TYPE_5__ zend_generator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_11__ {TYPE_2__* func; } ;
struct TYPE_9__ {int fn_flags; } ;
struct TYPE_10__ {TYPE_1__ op_array; } ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_4__* emalloc (int) ; 
 int /*<<< orphan*/  zend_generator_iterator_functions ; 
 int /*<<< orphan*/  zend_iterator_init (TYPE_4__*) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

zend_object_iterator *zend_generator_get_iterator(zend_class_entry *ce, zval *object, int by_ref) /* {{{ */
{
	zend_object_iterator *iterator;
	zend_generator *generator = (zend_generator*)Z_OBJ_P(object);

	if (!generator->execute_data) {
		zend_throw_exception(NULL, "Cannot traverse an already closed generator", 0);
		return NULL;
	}

	if (UNEXPECTED(by_ref) && !(generator->execute_data->func->op_array.fn_flags & ZEND_ACC_RETURN_REFERENCE)) {
		zend_throw_exception(NULL, "You can only iterate a generator by-reference if it declared that it yields by-reference", 0);
		return NULL;
	}

	iterator = generator->iterator = emalloc(sizeof(zend_object_iterator));

	zend_iterator_init(iterator);

	iterator->funcs = &zend_generator_iterator_functions;
	Z_ADDREF_P(object);
	ZVAL_OBJ(&iterator->data, Z_OBJ_P(object));

	return iterator;
}