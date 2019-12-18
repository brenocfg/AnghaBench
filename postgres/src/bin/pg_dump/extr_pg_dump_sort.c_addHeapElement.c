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

/* Variables and functions */

__attribute__((used)) static void
addHeapElement(int val, int *heap, int heapLength)
{
	int			j;

	/*
	 * Sift-up the new entry, per Knuth 5.2.3 exercise 16. Note that Knuth is
	 * using 1-based array indexes, not 0-based.
	 */
	j = heapLength;
	while (j > 0)
	{
		int			i = (j - 1) >> 1;

		if (val <= heap[i])
			break;
		heap[j] = heap[i];
		j = i;
	}
	heap[j] = val;
}