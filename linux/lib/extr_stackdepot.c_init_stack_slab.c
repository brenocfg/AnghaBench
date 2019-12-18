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
 size_t depot_index ; 
 int /*<<< orphan*/  next_slab_inited ; 
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** stack_slabs ; 

__attribute__((used)) static bool init_stack_slab(void **prealloc)
{
	if (!*prealloc)
		return false;
	/*
	 * This smp_load_acquire() pairs with smp_store_release() to
	 * |next_slab_inited| below and in depot_alloc_stack().
	 */
	if (smp_load_acquire(&next_slab_inited))
		return true;
	if (stack_slabs[depot_index] == NULL) {
		stack_slabs[depot_index] = *prealloc;
	} else {
		stack_slabs[depot_index + 1] = *prealloc;
		/*
		 * This smp_store_release pairs with smp_load_acquire() from
		 * |next_slab_inited| above and in stack_depot_save().
		 */
		smp_store_release(&next_slab_inited, 1);
	}
	*prealloc = NULL;
	return true;
}