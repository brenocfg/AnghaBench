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
struct ion_heap {size_t free_list_size; int /*<<< orphan*/  free_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

size_t ion_heap_freelist_size(struct ion_heap *heap)
{
	size_t size;

	spin_lock(&heap->free_lock);
	size = heap->free_list_size;
	spin_unlock(&heap->free_lock);

	return size;
}