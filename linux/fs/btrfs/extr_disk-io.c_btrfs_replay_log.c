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
struct btrfs_super_block {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  node; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sb; scalar_t__ generation; struct btrfs_super_block* super_copy; } ;
struct btrfs_fs_devices {scalar_t__ rw_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_TREE_LOG_OBJECTID ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __setup_root (struct btrfs_root*,struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct btrfs_root* btrfs_alloc_root (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfs_commit_super (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*) ; 
 int /*<<< orphan*/  btrfs_handle_fs_error (struct btrfs_fs_info*,int,char*) ; 
 int btrfs_recover_log_trees (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_super_log_root (struct btrfs_super_block*) ; 
 int btrfs_super_log_root_level (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*) ; 
 int /*<<< orphan*/  extent_buffer_uptodate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_root*) ; 
 int /*<<< orphan*/  read_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_replay_log(struct btrfs_fs_info *fs_info,
			    struct btrfs_fs_devices *fs_devices)
{
	int ret;
	struct btrfs_root *log_tree_root;
	struct btrfs_super_block *disk_super = fs_info->super_copy;
	u64 bytenr = btrfs_super_log_root(disk_super);
	int level = btrfs_super_log_root_level(disk_super);

	if (fs_devices->rw_devices == 0) {
		btrfs_warn(fs_info, "log replay required on RO media");
		return -EIO;
	}

	log_tree_root = btrfs_alloc_root(fs_info, GFP_KERNEL);
	if (!log_tree_root)
		return -ENOMEM;

	__setup_root(log_tree_root, fs_info, BTRFS_TREE_LOG_OBJECTID);

	log_tree_root->node = read_tree_block(fs_info, bytenr,
					      fs_info->generation + 1,
					      level, NULL);
	if (IS_ERR(log_tree_root->node)) {
		btrfs_warn(fs_info, "failed to read log tree");
		ret = PTR_ERR(log_tree_root->node);
		kfree(log_tree_root);
		return ret;
	} else if (!extent_buffer_uptodate(log_tree_root->node)) {
		btrfs_err(fs_info, "failed to read log tree");
		free_extent_buffer(log_tree_root->node);
		kfree(log_tree_root);
		return -EIO;
	}
	/* returns with log_tree_root freed on success */
	ret = btrfs_recover_log_trees(log_tree_root);
	if (ret) {
		btrfs_handle_fs_error(fs_info, ret,
				      "Failed to recover log tree");
		free_extent_buffer(log_tree_root->node);
		kfree(log_tree_root);
		return ret;
	}

	if (sb_rdonly(fs_info->sb)) {
		ret = btrfs_commit_super(fs_info);
		if (ret)
			return ret;
	}

	return 0;
}