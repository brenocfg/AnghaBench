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
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
typedef  int /*<<< orphan*/  iterate_irefs_t ;

/* Variables and functions */
 int ENOENT ; 
 int iterate_inode_extrefs (int /*<<< orphan*/ ,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ *,void*) ; 
 int iterate_inode_refs (int /*<<< orphan*/ ,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int iterate_irefs(u64 inum, struct btrfs_root *fs_root,
			 struct btrfs_path *path, iterate_irefs_t *iterate,
			 void *ctx)
{
	int ret;
	int found_refs = 0;

	ret = iterate_inode_refs(inum, fs_root, path, iterate, ctx);
	if (!ret)
		++found_refs;
	else if (ret != -ENOENT)
		return ret;

	ret = iterate_inode_extrefs(inum, fs_root, path, iterate, ctx);
	if (ret == -ENOENT && found_refs)
		return 0;

	return ret;
}