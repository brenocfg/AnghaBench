#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_2__ root_key; TYPE_1__* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_extent_inline_ref {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nodesize; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int lookup_extent_backref (struct btrfs_trans_handle*,struct btrfs_path*,struct btrfs_extent_inline_ref**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_ref_exists(struct btrfs_trans_handle *trans,
			    struct btrfs_root *root, u64 bytenr, u64 parent,
			    int level)
{
	struct btrfs_path *path;
	struct btrfs_extent_inline_ref *iref;
	int ret;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	ret = lookup_extent_backref(trans, path, &iref, bytenr,
				    root->fs_info->nodesize, parent,
				    root->root_key.objectid, level, 0);
	btrfs_free_path(path);
	if (ret == -ENOENT)
		return 0;
	if (ret < 0)
		return ret;
	return 1;
}