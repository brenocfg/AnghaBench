#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_size; } ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct btrfs_free_space_ctl* free_ino_ctl; struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_io_ctl {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_free_space_ctl {int dummy; } ;
typedef  int /*<<< orphan*/  io_ctl ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 int __btrfs_write_out_cache (struct btrfs_root*,struct inode*,struct btrfs_free_space_ctl*,int /*<<< orphan*/ *,struct btrfs_io_ctl*,struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_metadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfs_wait_cache_io_root (struct btrfs_root*,struct btrfs_trans_handle*,struct btrfs_io_ctl*,struct btrfs_path*) ; 
 int /*<<< orphan*/  memset (struct btrfs_io_ctl*,int /*<<< orphan*/ ,int) ; 

int btrfs_write_out_ino_cache(struct btrfs_root *root,
			      struct btrfs_trans_handle *trans,
			      struct btrfs_path *path,
			      struct inode *inode)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	int ret;
	struct btrfs_io_ctl io_ctl;
	bool release_metadata = true;

	if (!btrfs_test_opt(fs_info, INODE_MAP_CACHE))
		return 0;

	memset(&io_ctl, 0, sizeof(io_ctl));
	ret = __btrfs_write_out_cache(root, inode, ctl, NULL, &io_ctl, trans);
	if (!ret) {
		/*
		 * At this point writepages() didn't error out, so our metadata
		 * reservation is released when the writeback finishes, at
		 * inode.c:btrfs_finish_ordered_io(), regardless of it finishing
		 * with or without an error.
		 */
		release_metadata = false;
		ret = btrfs_wait_cache_io_root(root, trans, &io_ctl, path);
	}

	if (ret) {
		if (release_metadata)
			btrfs_delalloc_release_metadata(BTRFS_I(inode),
					inode->i_size, true);
#ifdef DEBUG
		btrfs_err(fs_info,
			  "failed to write free ino cache for root %llu",
			  root->root_key.objectid);
#endif
	}

	return ret;
}