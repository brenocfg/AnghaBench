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
struct TYPE_5__ {int count; int max_size; size_t elem_size; scalar_t__ (* cmp ) (void*,void*,void*) ;int /*<<< orphan*/  flags; scalar_t__ elements; } ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPL_HEAP_CORRUPTED ; 
 scalar_t__ erealloc (scalar_t__,int) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 void* spl_heap_elem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spl_heap_elem_copy (TYPE_1__*,void*,void*) ; 
 scalar_t__ stub1 (void*,void*,void*) ; 

__attribute__((used)) static void spl_ptr_heap_insert(spl_ptr_heap *heap, void *elem, void *cmp_userdata) { /* {{{ */
	int i;

	if (heap->count+1 > heap->max_size) {
		size_t alloc_size = heap->max_size * heap->elem_size;
		/* we need to allocate more memory */
		heap->elements  = erealloc(heap->elements, 2 * alloc_size);
		memset((char *) heap->elements + alloc_size, 0, alloc_size);
		heap->max_size *= 2;
	}

	/* sifting up */
	for (i = heap->count; i > 0 && heap->cmp(spl_heap_elem(heap, (i-1)/2), elem, cmp_userdata) < 0; i = (i-1)/2) {
		spl_heap_elem_copy(heap, spl_heap_elem(heap, i), spl_heap_elem(heap, (i-1)/2));
	}
	heap->count++;

	if (EG(exception)) {
		/* exception thrown during comparison */
		heap->flags |= SPL_HEAP_CORRUPTED;
	}

	spl_heap_elem_copy(heap, spl_heap_elem(heap, i), elem);
}