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
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int lazy_max_pages () ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_purge_vmap_area_lazy () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmap_lazy_nr ; 
 int /*<<< orphan*/  vmap_purge_list ; 

__attribute__((used)) static void free_vmap_area_noflush(struct vmap_area *va)
{
	int nr_lazy;

	nr_lazy = atomic_add_return((va->va_end - va->va_start) >> PAGE_SHIFT,
				    &vmap_lazy_nr);

	/* After this point, we may free va at any time */
	llist_add(&va->purge_list, &vmap_purge_list);

	if (unlikely(nr_lazy > lazy_max_pages()))
		try_purge_vmap_area_lazy();
}