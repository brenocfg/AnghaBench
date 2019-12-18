#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/ * postfix; int /*<<< orphan*/ * prefix; int /*<<< orphan*/  std; scalar_t__ level; int /*<<< orphan*/ * iterators; } ;
typedef  TYPE_1__ spl_recursive_it_object ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* spl_recursive_it_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_RecursiveIteratorIterator_free_storage(zend_object *_object)
{
	spl_recursive_it_object *object = spl_recursive_it_from_obj(_object);

	if (object->iterators) {
		efree(object->iterators);
		object->iterators = NULL;
		object->level     = 0;
	}

	zend_object_std_dtor(&object->std);
	smart_str_free(&object->prefix[0]);
	smart_str_free(&object->prefix[1]);
	smart_str_free(&object->prefix[2]);
	smart_str_free(&object->prefix[3]);
	smart_str_free(&object->prefix[4]);
	smart_str_free(&object->prefix[5]);

	smart_str_free(&object->postfix[0]);
}