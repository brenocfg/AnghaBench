#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bh_has_heap_property; scalar_t__ bh_size; } ;
typedef  TYPE_1__ binaryheap ;

/* Variables and functions */
 int parent_offset (scalar_t__) ; 
 int /*<<< orphan*/  sift_down (TYPE_1__*,int) ; 

void
binaryheap_build(binaryheap *heap)
{
	int			i;

	for (i = parent_offset(heap->bh_size - 1); i >= 0; i--)
		sift_down(heap, i);
	heap->bh_has_heap_property = true;
}