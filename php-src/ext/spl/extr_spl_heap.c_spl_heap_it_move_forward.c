#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_8__ {TYPE_4__* heap; } ;
typedef  TYPE_2__ spl_heap_object ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int SPL_HEAP_CORRUPTED ; 
 TYPE_2__* Z_SPLHEAP_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  spl_ptr_heap_delete_top (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_user_it_invalidate_current (TYPE_1__*) ; 

__attribute__((used)) static void spl_heap_it_move_forward(zend_object_iterator *iter) /* {{{ */
{
	spl_heap_object *object = Z_SPLHEAP_P(&iter->data);

	if (object->heap->flags & SPL_HEAP_CORRUPTED) {
		zend_throw_exception(spl_ce_RuntimeException, "Heap is corrupted, heap properties are no longer ensured.", 0);
		return;
	}

	spl_ptr_heap_delete_top(object->heap, NULL, &iter->data);
	zend_user_it_invalidate_current(iter);
}