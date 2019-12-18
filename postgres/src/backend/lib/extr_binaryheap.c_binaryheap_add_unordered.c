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
struct TYPE_3__ {size_t bh_size; size_t bh_space; int bh_has_heap_property; int /*<<< orphan*/ * bh_nodes; } ;
typedef  TYPE_1__ binaryheap ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
binaryheap_add_unordered(binaryheap *heap, Datum d)
{
	if (heap->bh_size >= heap->bh_space)
		elog(ERROR, "out of binary heap slots");
	heap->bh_has_heap_property = false;
	heap->bh_nodes[heap->bh_size] = d;
	heap->bh_size++;
}