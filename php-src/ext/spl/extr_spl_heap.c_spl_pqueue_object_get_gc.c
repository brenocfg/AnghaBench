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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {TYPE_1__* heap; } ;
typedef  TYPE_2__ spl_heap_object ;
struct TYPE_4__ {int count; scalar_t__ elements; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 TYPE_2__* spl_heap_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *spl_pqueue_object_get_gc(zend_object *obj, zval **gc_data, int *gc_data_count) /* {{{ */
{
	spl_heap_object *intern = spl_heap_from_obj(obj);
	*gc_data = (zval *) intern->heap->elements;
	/* Two zvals (value and priority) per pqueue entry */
	*gc_data_count = 2 * intern->heap->count;

	return zend_std_get_properties(obj);
}