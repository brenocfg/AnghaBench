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
struct TYPE_3__ {int count; int max_size; scalar_t__ (* cmp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/ * elements; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPL_HEAP_CORRUPTED ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * erealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void spl_ptr_heap_insert(spl_ptr_heap *heap, zval *elem, void *cmp_userdata) { /* {{{ */
	int i;

	if (heap->count+1 > heap->max_size) {
		/* we need to allocate more memory */
		heap->elements  = erealloc(heap->elements, heap->max_size * 2 * sizeof(zval));
		memset(heap->elements + heap->max_size, 0, heap->max_size * sizeof(zval));
		heap->max_size *= 2;
	}

	/* sifting up */
	for (i = heap->count; i > 0 && heap->cmp(&heap->elements[(i-1)/2], elem, cmp_userdata) < 0; i = (i-1)/2) {
		heap->elements[i] = heap->elements[(i-1)/2];
	}
	heap->count++;

	if (EG(exception)) {
		/* exception thrown during comparison */
		heap->flags |= SPL_HEAP_CORRUPTED;
	}

	ZVAL_COPY_VALUE(&heap->elements[i], elem);
}