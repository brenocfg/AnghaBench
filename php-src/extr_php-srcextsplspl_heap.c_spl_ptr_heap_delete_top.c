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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int count; scalar_t__ (* cmp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/ * elements; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPL_HEAP_CORRUPTED ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void spl_ptr_heap_delete_top(spl_ptr_heap *heap, zval *elem, void *cmp_userdata) { /* {{{ */
	int i, j;
	const int limit = (heap->count-1)/2;
	zval *bottom;

	if (heap->count == 0) {
		ZVAL_UNDEF(elem);
		return;
	}

	ZVAL_COPY_VALUE(elem, &heap->elements[0]);
	bottom = &heap->elements[--heap->count];

	for (i = 0; i < limit; i = j) {
		/* Find smaller child */
		j = i * 2 + 1;
		if(j != heap->count && heap->cmp(&heap->elements[j+1], &heap->elements[j], cmp_userdata) > 0) {
			j++; /* next child is bigger */
		}

		/* swap elements between two levels */
		if(heap->cmp(bottom, &heap->elements[j], cmp_userdata) < 0) {
			heap->elements[i] = heap->elements[j];
		} else {
			break;
		}
	}

	if (EG(exception)) {
		/* exception thrown during comparison */
		heap->flags |= SPL_HEAP_CORRUPTED;
	}

	ZVAL_COPY_VALUE(&heap->elements[i], bottom);
}