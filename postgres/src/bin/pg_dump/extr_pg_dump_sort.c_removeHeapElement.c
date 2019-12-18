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

__attribute__((used)) static int
removeHeapElement(int *heap, int heapLength)
{
	int			result = heap[0];
	int			val;
	int			i;

	if (--heapLength <= 0)
		return result;
	val = heap[heapLength];		/* value that must be reinserted */
	i = 0;						/* i is where the "hole" is */
	for (;;)
	{
		int			j = 2 * i + 1;

		if (j >= heapLength)
			break;
		if (j + 1 < heapLength &&
			heap[j] < heap[j + 1])
			j++;
		if (val >= heap[j])
			break;
		heap[i] = heap[j];
		i = j;
	}
	heap[i] = val;
	return result;
}