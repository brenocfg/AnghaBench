#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_sb; } ;
struct btrfs_trans_handle {struct btrfs_block_rsv* block_rsv; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_block_rsv {int failfast; void* size; } ;
struct btrfs_fs_info {struct btrfs_block_rsv trans_block_rsv; int /*<<< orphan*/  sectorsize; } ;
struct btrfs_clone_extent_info {scalar_t__ data_len; int /*<<< orphan*/  file_offset; int /*<<< orphan*/  data_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_RSV_TEMP ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_NEEDS_FULL_SYNC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  NO_HOLES ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int __btrfs_drop_extents (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,struct btrfs_path*,scalar_t__,scalar_t__ const,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 struct btrfs_block_rsv* btrfs_alloc_block_rsv (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfs_block_rsv_migrate (struct btrfs_block_rsv*,struct btrfs_block_rsv*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_fs_info*) ; 
 void* btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_free_block_rsv (struct btrfs_fs_info*,struct btrfs_block_rsv*) ; 
 int /*<<< orphan*/  btrfs_fs_incompat (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfs_insert_clone_extent (struct btrfs_trans_handle*,struct inode*,struct btrfs_path*,struct btrfs_clone_extent_info*,scalar_t__) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,unsigned int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int fill_holes (struct btrfs_trans_handle*,TYPE_1__*,struct btrfs_path*,scalar_t__,scalar_t__) ; 
 int find_first_non_hole (struct inode*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_punch_hole_range(struct inode *inode, struct btrfs_path *path,
			   const u64 start, const u64 end,
			   struct btrfs_clone_extent_info *clone_info,
			   struct btrfs_trans_handle **trans_out)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 min_size = btrfs_calc_insert_metadata_size(fs_info, 1);
	u64 ino_size = round_up(inode->i_size, fs_info->sectorsize);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans = NULL;
	struct btrfs_block_rsv *rsv;
	unsigned int rsv_count;
	u64 cur_offset;
	u64 drop_end;
	u64 len = end - start;
	int ret = 0;

	if (end <= start)
		return -EINVAL;

	rsv = btrfs_alloc_block_rsv(fs_info, BTRFS_BLOCK_RSV_TEMP);
	if (!rsv) {
		ret = -ENOMEM;
		goto out;
	}
	rsv->size = btrfs_calc_insert_metadata_size(fs_info, 1);
	rsv->failfast = 1;

	/*
	 * 1 - update the inode
	 * 1 - removing the extents in the range
	 * 1 - adding the hole extent if no_holes isn't set or if we are cloning
	 *     an extent
	 */
	if (!btrfs_fs_incompat(fs_info, NO_HOLES) || clone_info)
		rsv_count = 3;
	else
		rsv_count = 2;

	trans = btrfs_start_transaction(root, rsv_count);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		trans = NULL;
		goto out_free;
	}

	ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv, rsv,
				      min_size, false);
	BUG_ON(ret);
	trans->block_rsv = rsv;

	cur_offset = start;
	while (cur_offset < end) {
		ret = __btrfs_drop_extents(trans, root, inode, path,
					   cur_offset, end + 1, &drop_end,
					   1, 0, 0, NULL);
		if (ret != -ENOSPC) {
			/*
			 * When cloning we want to avoid transaction aborts when
			 * nothing was done and we are attempting to clone parts
			 * of inline extents, in such cases -EOPNOTSUPP is
			 * returned by __btrfs_drop_extents() without having
			 * changed anything in the file.
			 */
			if (clone_info && ret && ret != -EOPNOTSUPP)
				btrfs_abort_transaction(trans, ret);
			break;
		}

		trans->block_rsv = &fs_info->trans_block_rsv;

		if (!clone_info && cur_offset < drop_end &&
		    cur_offset < ino_size) {
			ret = fill_holes(trans, BTRFS_I(inode), path,
					cur_offset, drop_end);
			if (ret) {
				/*
				 * If we failed then we didn't insert our hole
				 * entries for the area we dropped, so now the
				 * fs is corrupted, so we must abort the
				 * transaction.
				 */
				btrfs_abort_transaction(trans, ret);
				break;
			}
		}

		if (clone_info) {
			u64 clone_len = drop_end - cur_offset;

			ret = btrfs_insert_clone_extent(trans, inode, path,
							clone_info, clone_len);
			if (ret) {
				btrfs_abort_transaction(trans, ret);
				break;
			}
			clone_info->data_len -= clone_len;
			clone_info->data_offset += clone_len;
			clone_info->file_offset += clone_len;
		}

		cur_offset = drop_end;

		ret = btrfs_update_inode(trans, root, inode);
		if (ret)
			break;

		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		trans = btrfs_start_transaction(root, rsv_count);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			trans = NULL;
			break;
		}

		ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv,
					      rsv, min_size, false);
		BUG_ON(ret);	/* shouldn't happen */
		trans->block_rsv = rsv;

		if (!clone_info) {
			ret = find_first_non_hole(inode, &cur_offset, &len);
			if (unlikely(ret < 0))
				break;
			if (ret && !len) {
				ret = 0;
				break;
			}
		}
	}

	/*
	 * If we were cloning, force the next fsync to be a full one since we
	 * we replaced (or just dropped in the case of cloning holes when
	 * NO_HOLES is enabled) extents and extent maps.
	 * This is for the sake of simplicity, and cloning into files larger
	 * than 16Mb would force the full fsync any way (when
	 * try_release_extent_mapping() is invoked during page cache truncation.
	 */
	if (clone_info)
		set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
			&BTRFS_I(inode)->runtime_flags);

	if (ret)
		goto out_trans;

	trans->block_rsv = &fs_info->trans_block_rsv;
	/*
	 * If we are using the NO_HOLES feature we might have had already an
	 * hole that overlaps a part of the region [lockstart, lockend] and
	 * ends at (or beyond) lockend. Since we have no file extent items to
	 * represent holes, drop_end can be less than lockend and so we must
	 * make sure we have an extent map representing the existing hole (the
	 * call to __btrfs_drop_extents() might have dropped the existing extent
	 * map representing the existing hole), otherwise the fast fsync path
	 * will not record the existence of the hole region
	 * [existing_hole_start, lockend].
	 */
	if (drop_end <= end)
		drop_end = end + 1;
	/*
	 * Don't insert file hole extent item if it's for a range beyond eof
	 * (because it's useless) or if it represents a 0 bytes range (when
	 * cur_offset == drop_end).
	 */
	if (!clone_info && cur_offset < ino_size && cur_offset < drop_end) {
		ret = fill_holes(trans, BTRFS_I(inode), path,
				cur_offset, drop_end);
		if (ret) {
			/* Same comment as above. */
			btrfs_abort_transaction(trans, ret);
			goto out_trans;
		}
	}
	if (clone_info) {
		ret = btrfs_insert_clone_extent(trans, inode, path, clone_info,
						clone_info->data_len);
		if (ret) {
			btrfs_abort_transaction(trans, ret);
			goto out_trans;
		}
	}

out_trans:
	if (!trans)
		goto out_free;

	trans->block_rsv = &fs_info->trans_block_rsv;
	if (ret)
		btrfs_end_transaction(trans);
	else
		*trans_out = trans;
out_free:
	btrfs_free_block_rsv(fs_info, rsv);
out:
	return ret;
}