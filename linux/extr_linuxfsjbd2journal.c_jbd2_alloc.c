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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 size_t PAGE_SIZE ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  get_slab (size_t) ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *jbd2_alloc(size_t size, gfp_t flags)
{
	void *ptr;

	BUG_ON(size & (size-1)); /* Must be a power of 2 */

	if (size < PAGE_SIZE)
		ptr = kmem_cache_alloc(get_slab(size), flags);
	else
		ptr = (void *)__get_free_pages(flags, get_order(size));

	/* Check alignment; SLUB has gotten this wrong in the past,
	 * and this can lead to user data corruption! */
	BUG_ON(((unsigned long) ptr) & (size-1));

	return ptr;
}