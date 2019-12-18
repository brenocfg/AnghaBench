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
struct vmap_area {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_vmap_area_list ; 
 int /*<<< orphan*/  free_vmap_area_root ; 
 int /*<<< orphan*/  merge_or_add_vmap_area (struct vmap_area*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_va (struct vmap_area*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmap_area_root ; 

__attribute__((used)) static void __free_vmap_area(struct vmap_area *va)
{
	/*
	 * Remove from the busy tree/list.
	 */
	unlink_va(va, &vmap_area_root);

	/*
	 * Merge VA with its neighbors, otherwise just add it.
	 */
	merge_or_add_vmap_area(va,
		&free_vmap_area_root, &free_vmap_area_list);
}