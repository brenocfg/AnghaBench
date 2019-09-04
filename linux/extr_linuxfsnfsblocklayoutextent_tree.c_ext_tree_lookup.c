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
struct pnfs_block_layout {int /*<<< orphan*/  bl_ext_lock; int /*<<< orphan*/  bl_ext_rw; int /*<<< orphan*/  bl_ext_ro; } ;
struct pnfs_block_extent {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int __ext_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pnfs_block_extent*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool
ext_tree_lookup(struct pnfs_block_layout *bl, sector_t isect,
	    struct pnfs_block_extent *ret, bool rw)
{
	bool found = false;

	spin_lock(&bl->bl_ext_lock);
	if (!rw)
		found = __ext_tree_lookup(&bl->bl_ext_ro, isect, ret);
	if (!found)
		found = __ext_tree_lookup(&bl->bl_ext_rw, isect, ret);
	spin_unlock(&bl->bl_ext_lock);

	return found;
}