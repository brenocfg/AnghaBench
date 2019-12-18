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
struct vmap_area {int va_end; int va_start; int /*<<< orphan*/  purge_list; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long atomic_long_add_return (int,int /*<<< orphan*/ *) ; 
 unsigned long lazy_max_pages () ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_purge_vmap_area_lazy () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlink_va (struct vmap_area*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmap_area_lock ; 
 int /*<<< orphan*/  vmap_area_root ; 
 int /*<<< orphan*/  vmap_lazy_nr ; 
 int /*<<< orphan*/  vmap_purge_list ; 

__attribute__((used)) static void free_vmap_area_noflush(struct vmap_area *va)
{
	unsigned long nr_lazy;

	spin_lock(&vmap_area_lock);
	unlink_va(va, &vmap_area_root);
	spin_unlock(&vmap_area_lock);

	nr_lazy = atomic_long_add_return((va->va_end - va->va_start) >>
				PAGE_SHIFT, &vmap_lazy_nr);

	/* After this point, we may free va at any time */
	llist_add(&va->purge_list, &vmap_purge_list);

	if (unlikely(nr_lazy > lazy_max_pages()))
		try_purge_vmap_area_lazy();
}