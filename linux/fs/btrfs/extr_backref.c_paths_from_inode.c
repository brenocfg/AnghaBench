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
typedef  int /*<<< orphan*/  u64 ;
struct inode_fs_paths {int /*<<< orphan*/  btrfs_path; int /*<<< orphan*/  fs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_to_path ; 
 int iterate_irefs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode_fs_paths*) ; 

int paths_from_inode(u64 inum, struct inode_fs_paths *ipath)
{
	return iterate_irefs(inum, ipath->fs_root, ipath->btrfs_path,
			     inode_to_path, ipath);
}