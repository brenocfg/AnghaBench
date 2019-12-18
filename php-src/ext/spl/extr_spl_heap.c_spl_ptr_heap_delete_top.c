#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; scalar_t__ (* cmp ) (void*,void*,void*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  (* dtor ) (void*) ;} ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int /*<<< orphan*/  SPL_HEAP_CORRUPTED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  exception ; 
 void* spl_heap_elem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spl_heap_elem_copy (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 scalar_t__ stub2 (void*,void*,void*) ; 
 scalar_t__ stub3 (void*,void*,void*) ; 

__attribute__((used)) static int spl_ptr_heap_delete_top(spl_ptr_heap *heap, void *elem, void *cmp_userdata) { /* {{{ */
	int i, j;
	const int limit = (heap->count-1)/2;
	void *bottom;

	if (heap->count == 0) {
		return FAILURE;
	}

	if (elem) {
		spl_heap_elem_copy(heap, elem, spl_heap_elem(heap, 0));
	} else {
		heap->dtor(spl_heap_elem(heap, 0));
	}

	bottom = spl_heap_elem(heap, --heap->count);

	for (i = 0; i < limit; i = j) {
		/* Find smaller child */
		j = i * 2 + 1;
		if (j != heap->count && heap->cmp(spl_heap_elem(heap, j+1), spl_heap_elem(heap, j), cmp_userdata) > 0) {
			j++; /* next child is bigger */
		}

		/* swap elements between two levels */
		if(heap->cmp(bottom, spl_heap_elem(heap, j), cmp_userdata) < 0) {
			spl_heap_elem_copy(heap, spl_heap_elem(heap, i), spl_heap_elem(heap, j));
		} else {
			break;
		}
	}

	if (EG(exception)) {
		/* exception thrown during comparison */
		heap->flags |= SPL_HEAP_CORRUPTED;
	}

	spl_heap_elem_copy(heap, spl_heap_elem(heap, i), bottom);
	return SUCCESS;
}