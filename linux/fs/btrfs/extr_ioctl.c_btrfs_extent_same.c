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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {int /*<<< orphan*/  root_item_lock; int /*<<< orphan*/  dedupe_in_progress; scalar_t__ send_in_progress; TYPE_1__ root_key; int /*<<< orphan*/  fs_info; } ;
struct TYPE_4__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_MAX_DEDUPE_LEN ; 
 int EAGAIN ; 
 int btrfs_extent_same_range (struct inode*,scalar_t__,scalar_t__,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_warn_rl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ div_u64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_extent_same(struct inode *src, u64 loff, u64 olen,
			     struct inode *dst, u64 dst_loff)
{
	int ret;
	u64 i, tail_len, chunk_count;
	struct btrfs_root *root_dst = BTRFS_I(dst)->root;

	spin_lock(&root_dst->root_item_lock);
	if (root_dst->send_in_progress) {
		btrfs_warn_rl(root_dst->fs_info,
"cannot deduplicate to root %llu while send operations are using it (%d in progress)",
			      root_dst->root_key.objectid,
			      root_dst->send_in_progress);
		spin_unlock(&root_dst->root_item_lock);
		return -EAGAIN;
	}
	root_dst->dedupe_in_progress++;
	spin_unlock(&root_dst->root_item_lock);

	tail_len = olen % BTRFS_MAX_DEDUPE_LEN;
	chunk_count = div_u64(olen, BTRFS_MAX_DEDUPE_LEN);

	for (i = 0; i < chunk_count; i++) {
		ret = btrfs_extent_same_range(src, loff, BTRFS_MAX_DEDUPE_LEN,
					      dst, dst_loff);
		if (ret)
			goto out;

		loff += BTRFS_MAX_DEDUPE_LEN;
		dst_loff += BTRFS_MAX_DEDUPE_LEN;
	}

	if (tail_len > 0)
		ret = btrfs_extent_same_range(src, loff, tail_len, dst,
					      dst_loff);
out:
	spin_lock(&root_dst->root_item_lock);
	root_dst->dedupe_in_progress--;
	spin_unlock(&root_dst->root_item_lock);

	return ret;
}