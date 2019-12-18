#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_2__ it; int /*<<< orphan*/  value; int /*<<< orphan*/ * ce; } ;
typedef  TYPE_1__ zend_user_iterator ;
typedef  TYPE_2__ zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_10__ {int ar_flags; } ;
typedef  TYPE_3__ spl_array_object ;

/* Variables and functions */
 int SPL_ARRAY_OVERLOADED_CURRENT ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  spl_array_it_funcs ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  zend_iterator_init (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

zend_object_iterator *spl_array_get_iterator(zend_class_entry *ce, zval *object, int by_ref) /* {{{ */
{
	zend_user_iterator *iterator;
	spl_array_object *array_object = Z_SPLARRAY_P(object);

	if (by_ref && (array_object->ar_flags & SPL_ARRAY_OVERLOADED_CURRENT)) {
		zend_throw_exception(spl_ce_RuntimeException, "An iterator cannot be used with foreach by reference", 0);
		return NULL;
	}

	iterator = emalloc(sizeof(zend_user_iterator));

	zend_iterator_init(&iterator->it);

	Z_ADDREF_P(object);
	ZVAL_OBJ(&iterator->it.data, Z_OBJ_P(object));
	iterator->it.funcs = &spl_array_it_funcs;
	iterator->ce = ce;
	ZVAL_UNDEF(&iterator->value);

	return &iterator->it;
}