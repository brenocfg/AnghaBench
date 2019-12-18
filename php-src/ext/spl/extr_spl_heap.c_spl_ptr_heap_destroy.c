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
struct TYPE_5__ {int count; struct TYPE_5__* elements; int /*<<< orphan*/  (* dtor ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  spl_heap_elem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spl_ptr_heap_destroy(spl_ptr_heap *heap) { /* {{{ */
	int i;

	for (i = 0; i < heap->count; ++i) {
		heap->dtor(spl_heap_elem(heap, i));
	}

	efree(heap->elements);
	efree(heap);
}