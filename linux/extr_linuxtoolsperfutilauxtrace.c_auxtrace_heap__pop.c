#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct auxtrace_heap_item {scalar_t__ ordinal; int /*<<< orphan*/  queue_nr; } ;
struct auxtrace_heap {unsigned int heap_cnt; struct auxtrace_heap_item* heap_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_heapify (struct auxtrace_heap_item*,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 

void auxtrace_heap__pop(struct auxtrace_heap *heap)
{
	unsigned int pos, last, heap_cnt = heap->heap_cnt;
	struct auxtrace_heap_item *heap_array;

	if (!heap_cnt)
		return;

	heap->heap_cnt -= 1;

	heap_array = heap->heap_array;

	pos = 0;
	while (1) {
		unsigned int left, right;

		left = (pos << 1) + 1;
		if (left >= heap_cnt)
			break;
		right = left + 1;
		if (right >= heap_cnt) {
			heap_array[pos] = heap_array[left];
			return;
		}
		if (heap_array[left].ordinal < heap_array[right].ordinal) {
			heap_array[pos] = heap_array[left];
			pos = left;
		} else {
			heap_array[pos] = heap_array[right];
			pos = right;
		}
	}

	last = heap_cnt - 1;
	auxtrace_heapify(heap_array, pos, heap_array[last].queue_nr,
			 heap_array[last].ordinal);
}