#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {size_t level; TYPE_3__* iterators; } ;
typedef  TYPE_1__ spl_recursive_it_object ;
struct TYPE_5__ {int /*<<< orphan*/  zobject; int /*<<< orphan*/ * iterator; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_3__*) ; 
 TYPE_1__* spl_recursive_it_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_iterator_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_objects_destroy_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_RecursiveIteratorIterator_dtor(zend_object *_object)
{
	spl_recursive_it_object *object = spl_recursive_it_from_obj(_object);
	zend_object_iterator *sub_iter;

	/* call standard dtor */
	zend_objects_destroy_object(_object);

	if (object->iterators) {
		while (object->level >= 0) {
			sub_iter = object->iterators[object->level].iterator;
			zend_iterator_dtor(sub_iter);
			zval_ptr_dtor(&object->iterators[object->level--].zobject);
		}
		efree(object->iterators);
		object->iterators = NULL;
	}
}