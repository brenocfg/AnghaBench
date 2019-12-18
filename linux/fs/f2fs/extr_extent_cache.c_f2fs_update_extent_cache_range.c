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
struct dnode_of_data {int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  f2fs_may_extent_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_extent_tree_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void f2fs_update_extent_cache_range(struct dnode_of_data *dn,
				pgoff_t fofs, block_t blkaddr, unsigned int len)

{
	if (!f2fs_may_extent_tree(dn->inode))
		return;

	f2fs_update_extent_tree_range(dn->inode, fofs, blkaddr, len);
}