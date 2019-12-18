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
struct TYPE_5__ {int bh_size; int /*<<< orphan*/ * bh_nodes; scalar_t__ bh_has_heap_property; } ;
typedef  TYPE_1__ binaryheap ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  binaryheap_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  sift_down (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
binaryheap_replace_first(binaryheap *heap, Datum d)
{
	Assert(!binaryheap_empty(heap) && heap->bh_has_heap_property);

	heap->bh_nodes[0] = d;

	if (heap->bh_size > 1)
		sift_down(heap, 0);
}