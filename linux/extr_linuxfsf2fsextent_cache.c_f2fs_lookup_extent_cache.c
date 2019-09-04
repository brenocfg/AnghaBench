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
struct inode {int dummy; } ;
struct extent_info {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int f2fs_lookup_extent_tree (struct inode*,int /*<<< orphan*/ ,struct extent_info*) ; 
 int /*<<< orphan*/  f2fs_may_extent_tree (struct inode*) ; 

bool f2fs_lookup_extent_cache(struct inode *inode, pgoff_t pgofs,
					struct extent_info *ei)
{
	if (!f2fs_may_extent_tree(inode))
		return false;

	return f2fs_lookup_extent_tree(inode, pgofs, ei);
}