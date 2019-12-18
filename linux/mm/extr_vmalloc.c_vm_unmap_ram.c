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
struct vmap_area {unsigned long va_start; unsigned long va_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_ALIGNED (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long VMALLOC_END ; 
 unsigned long VMALLOC_START ; 
 unsigned int VMAP_MAX_ALLOC ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (void*,unsigned long) ; 
 struct vmap_area* find_vmap_area (unsigned long) ; 
 int /*<<< orphan*/  free_unmap_vmap_area (struct vmap_area*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  vb_free (void const*,unsigned long) ; 

void vm_unmap_ram(const void *mem, unsigned int count)
{
	unsigned long size = (unsigned long)count << PAGE_SHIFT;
	unsigned long addr = (unsigned long)mem;
	struct vmap_area *va;

	might_sleep();
	BUG_ON(!addr);
	BUG_ON(addr < VMALLOC_START);
	BUG_ON(addr > VMALLOC_END);
	BUG_ON(!PAGE_ALIGNED(addr));

	if (likely(count <= VMAP_MAX_ALLOC)) {
		debug_check_no_locks_freed(mem, size);
		vb_free(mem, size);
		return;
	}

	va = find_vmap_area(addr);
	BUG_ON(!va);
	debug_check_no_locks_freed((void *)va->va_start,
				    (va->va_end - va->va_start));
	free_unmap_vmap_area(va);
}