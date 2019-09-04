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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_delayed_extent_op {int update_flags; int update_key; int is_data; int level; int /*<<< orphan*/  flags_to_set; } ;

/* Variables and functions */
 int ENOMEM ; 
 int btrfs_add_delayed_extent_op (struct btrfs_fs_info*,struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_delayed_extent_op*) ; 
 struct btrfs_delayed_extent_op* btrfs_alloc_delayed_extent_op () ; 
 int /*<<< orphan*/  btrfs_free_delayed_extent_op (struct btrfs_delayed_extent_op*) ; 

int btrfs_set_disk_extent_flags(struct btrfs_trans_handle *trans,
				struct btrfs_fs_info *fs_info,
				u64 bytenr, u64 num_bytes, u64 flags,
				int level, int is_data)
{
	struct btrfs_delayed_extent_op *extent_op;
	int ret;

	extent_op = btrfs_alloc_delayed_extent_op();
	if (!extent_op)
		return -ENOMEM;

	extent_op->flags_to_set = flags;
	extent_op->update_flags = true;
	extent_op->update_key = false;
	extent_op->is_data = is_data ? true : false;
	extent_op->level = level;

	ret = btrfs_add_delayed_extent_op(fs_info, trans, bytenr,
					  num_bytes, extent_op);
	if (ret)
		btrfs_free_delayed_extent_op(extent_op);
	return ret;
}