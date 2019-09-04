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
struct vmap_area {int /*<<< orphan*/  va_end; int /*<<< orphan*/  va_start; } ;

/* Variables and functions */
 scalar_t__ debug_pagealloc_enabled () ; 
 int /*<<< orphan*/  flush_cache_vunmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_vmap_area_noflush (struct vmap_area*) ; 
 int /*<<< orphan*/  unmap_vmap_area (struct vmap_area*) ; 

__attribute__((used)) static void free_unmap_vmap_area(struct vmap_area *va)
{
	flush_cache_vunmap(va->va_start, va->va_end);
	unmap_vmap_area(va);
	if (debug_pagealloc_enabled())
		flush_tlb_kernel_range(va->va_start, va->va_end);

	free_vmap_area_noflush(va);
}