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
struct TYPE_3__ {int /*<<< orphan*/  heap; int /*<<< orphan*/  std; } ;
typedef  TYPE_1__ spl_heap_object ;

/* Variables and functions */
 TYPE_1__* spl_heap_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ptr_heap_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_heap_object_free_storage(zend_object *object) /* {{{ */
{
	spl_heap_object *intern = spl_heap_from_obj(object);

	zend_object_std_dtor(&intern->std);

	spl_ptr_heap_destroy(intern->heap);
}