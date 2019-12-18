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
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_5__ {int /*<<< orphan*/  priority; } ;
typedef  TYPE_1__ spl_pqueue_elem ;
struct TYPE_6__ {scalar_t__ fptr_cmp; } ;
typedef  TYPE_2__ spl_heap_object ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILURE ; 
 int ZEND_NORMALIZE_BOOL (int /*<<< orphan*/ ) ; 
 TYPE_2__* Z_SPLHEAP_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 scalar_t__ spl_ptr_heap_cmp_cb_helper (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_ptr_pqueue_elem_cmp(void *x, void *y, zval *object) { /* {{{ */
	spl_pqueue_elem *a = x;
	spl_pqueue_elem *b = y;
	zval *a_priority_p = &a->priority;
	zval *b_priority_p = &b->priority;

	if (EG(exception)) {
		return 0;
	}

	if (object) {
		spl_heap_object *heap_object = Z_SPLHEAP_P(object);
		if (heap_object->fptr_cmp) {
			zend_long lval = 0;
			if (spl_ptr_heap_cmp_cb_helper(object, heap_object, a_priority_p, b_priority_p, &lval) == FAILURE) {
				/* exception or call failure */
				return 0;
			}
			return ZEND_NORMALIZE_BOOL(lval);
		}
	}

	return zend_compare(a_priority_p, b_priority_p);
}