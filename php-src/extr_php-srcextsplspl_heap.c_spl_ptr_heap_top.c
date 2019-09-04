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
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *spl_ptr_heap_top(spl_ptr_heap *heap) { /* {{{ */
	if (heap->count == 0) {
		return NULL;
	}

	return Z_ISUNDEF(heap->elements[0])? NULL : &heap->elements[0];
}