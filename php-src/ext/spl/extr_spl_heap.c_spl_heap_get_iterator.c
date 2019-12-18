#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ spl_heap_object ;
struct TYPE_9__ {TYPE_2__ it; int /*<<< orphan*/  value; int /*<<< orphan*/ * ce; } ;
struct TYPE_12__ {TYPE_1__ intern; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ spl_heap_it ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_SPLHEAP_P (int /*<<< orphan*/ *) ; 
 TYPE_4__* emalloc (int) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  spl_heap_it_funcs ; 
 int /*<<< orphan*/  zend_iterator_init (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

zend_object_iterator *spl_heap_get_iterator(zend_class_entry *ce, zval *object, int by_ref) /* {{{ */
{
	spl_heap_it     *iterator;
	spl_heap_object *heap_object = Z_SPLHEAP_P(object);

	if (by_ref) {
		zend_throw_exception(spl_ce_RuntimeException, "An iterator cannot be used with foreach by reference", 0);
		return NULL;
	}

	iterator = emalloc(sizeof(spl_heap_it));

	zend_iterator_init(&iterator->intern.it);

	Z_ADDREF_P(object);
	ZVAL_OBJ(&iterator->intern.it.data, Z_OBJ_P(object));
	iterator->intern.it.funcs = &spl_heap_it_funcs;
	iterator->intern.ce       = ce;
	iterator->flags           = heap_object->flags;
	ZVAL_UNDEF(&iterator->intern.value);

	return &iterator->intern.it;
}