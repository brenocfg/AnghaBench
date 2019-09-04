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
typedef  int /*<<< orphan*/  zend_object_iterator ;
typedef  int /*<<< orphan*/  spl_sub_iterator ;
struct TYPE_8__ {size_t level; TYPE_4__* iterators; } ;
typedef  TYPE_2__ spl_recursive_it_object ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ intern; } ;
typedef  TYPE_3__ spl_recursive_it_iterator ;
struct TYPE_10__ {int /*<<< orphan*/  zobject; int /*<<< orphan*/ * iterator; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 TYPE_2__* Z_SPLRECURSIVE_IT_P (int /*<<< orphan*/ *) ; 
 TYPE_4__* erealloc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  zend_iterator_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_recursive_it_dtor(zend_object_iterator *_iter)
{
	spl_recursive_it_iterator *iter   = (spl_recursive_it_iterator*)_iter;
	spl_recursive_it_object   *object = Z_SPLRECURSIVE_IT_P(&iter->intern.data);
	zend_object_iterator      *sub_iter;

	while (object->level > 0) {
		if (!Z_ISUNDEF(object->iterators[object->level].zobject)) {
			sub_iter = object->iterators[object->level].iterator;
			zend_iterator_dtor(sub_iter);
			zval_ptr_dtor(&object->iterators[object->level].zobject);
		}
		object->level--;
	}
	object->iterators = erealloc(object->iterators, sizeof(spl_sub_iterator));
	object->level = 0;

	zval_ptr_dtor(&iter->intern.data);
}