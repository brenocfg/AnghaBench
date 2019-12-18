#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_7__ {int /*<<< orphan*/ * iterators; } ;
typedef  TYPE_2__ spl_recursive_it_object ;
struct TYPE_6__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ intern; } ;
typedef  TYPE_3__ spl_recursive_it_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* Z_SPLRECURSIVE_IT_P (int /*<<< orphan*/ *) ; 
 TYPE_3__* emalloc (int) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  spl_recursive_it_iterator_funcs ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_iterator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object_iterator *spl_recursive_it_get_iterator(zend_class_entry *ce, zval *zobject, int by_ref)
{
	spl_recursive_it_iterator *iterator;
	spl_recursive_it_object *object;

	if (by_ref) {
		zend_throw_exception(spl_ce_RuntimeException, "An iterator cannot be used with foreach by reference", 0);
		return NULL;
	}
	iterator = emalloc(sizeof(spl_recursive_it_iterator));
	object   = Z_SPLRECURSIVE_IT_P(zobject);
	if (object->iterators == NULL) {
		zend_error(E_ERROR, "The object to be iterated is in an invalid state: "
				"the parent constructor has not been called");
	}

	zend_iterator_init((zend_object_iterator*)iterator);

	Z_ADDREF_P(zobject);
	ZVAL_OBJ(&iterator->intern.data, Z_OBJ_P(zobject));
	iterator->intern.funcs = &spl_recursive_it_iterator_funcs;
	return (zend_object_iterator*)iterator;
}