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
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct btrfs_root* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct btrfs_root *btrfs_alloc_root(struct btrfs_fs_info *fs_info,
		gfp_t flags)
{
	struct btrfs_root *root = kzalloc(sizeof(*root), flags);
	if (root)
		root->fs_info = fs_info;
	return root;
}