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
struct TYPE_4__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  ce; TYPE_1__ it; } ;
typedef  TYPE_2__ zend_user_iterator ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* emalloc (int) ; 
 int /*<<< orphan*/  zend_interface_iterator_funcs_iterator ; 
 int /*<<< orphan*/  zend_iterator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static zend_object_iterator *zend_user_it_get_iterator(zend_class_entry *ce, zval *object, int by_ref)
{
	zend_user_iterator *iterator;

	if (by_ref) {
		zend_throw_error(NULL, "An iterator cannot be used with foreach by reference");
		return NULL;
	}

	iterator = emalloc(sizeof(zend_user_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	Z_ADDREF_P(object);
	ZVAL_OBJ(&iterator->it.data, Z_OBJ_P(object));
	iterator->it.funcs = &zend_interface_iterator_funcs_iterator;
	iterator->ce = Z_OBJCE_P(object);
	ZVAL_UNDEF(&iterator->value);
	return (zend_object_iterator*)iterator;
}