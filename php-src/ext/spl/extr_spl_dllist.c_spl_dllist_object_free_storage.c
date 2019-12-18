#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {int /*<<< orphan*/  traverse_pointer; TYPE_2__* llist; int /*<<< orphan*/ * gc_data; int /*<<< orphan*/  std; } ;
typedef  TYPE_1__ spl_dllist_object ;
struct TYPE_6__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPL_LLIST_CHECK_DELREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 TYPE_1__* spl_dllist_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ptr_llist_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  spl_ptr_llist_pop (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_dllist_object_free_storage(zend_object *object) /* {{{ */
{
	spl_dllist_object *intern = spl_dllist_from_obj(object);
	zval tmp;

	zend_object_std_dtor(&intern->std);

	while (intern->llist->count > 0) {
		spl_ptr_llist_pop(intern->llist, &tmp);
		zval_ptr_dtor(&tmp);
	}

	if (intern->gc_data != NULL) {
		efree(intern->gc_data);
	};

	spl_ptr_llist_destroy(intern->llist);
	SPL_LLIST_CHECK_DELREF(intern->traverse_pointer);
}