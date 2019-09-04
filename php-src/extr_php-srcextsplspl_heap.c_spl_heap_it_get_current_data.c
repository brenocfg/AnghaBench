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
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zend_object_iterator ;
struct TYPE_8__ {TYPE_1__* heap; } ;
typedef  TYPE_3__ spl_heap_object ;
struct TYPE_6__ {int flags; scalar_t__ count; int /*<<< orphan*/ * elements; } ;

/* Variables and functions */
 int SPL_HEAP_CORRUPTED ; 
 scalar_t__ Z_ISUNDEF_P (int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_SPLHEAP_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *spl_heap_it_get_current_data(zend_object_iterator *iter) /* {{{ */
{
	spl_heap_object *object = Z_SPLHEAP_P(&iter->data);
	zval *element = &object->heap->elements[0];

	if (object->heap->flags & SPL_HEAP_CORRUPTED) {
		zend_throw_exception(spl_ce_RuntimeException, "Heap is corrupted, heap properties are no longer ensured.", 0);
		return NULL;
	}

	if (object->heap->count == 0 || Z_ISUNDEF_P(element)) {
		return NULL;
	} else {
		return element;
	}
}