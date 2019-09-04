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
struct vm_area_struct {struct gntdev_grant_map* vm_private_data; } ;
struct gntdev_grant_map {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gntdev_vma_open(struct vm_area_struct *vma)
{
	struct gntdev_grant_map *map = vma->vm_private_data;

	pr_debug("gntdev_vma_open %p\n", vma);
	refcount_inc(&map->users);
}