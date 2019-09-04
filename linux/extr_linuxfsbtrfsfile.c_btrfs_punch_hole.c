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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; } ;
struct extent_state {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_block_rsv* block_rsv; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_block_rsv {int failfast; void* size; } ;
struct btrfs_fs_info {scalar_t__ sectorsize; struct btrfs_block_rsv trans_block_rsv; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  io_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_RSV_TEMP ; 
 scalar_t__ BTRFS_BYTES_TO_BLKS (struct btrfs_fs_info*,scalar_t__) ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  NO_HOLES ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int __btrfs_drop_extents (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,struct btrfs_path*,scalar_t__,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 struct btrfs_block_rsv* btrfs_alloc_block_rsv (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_block_rsv_migrate (struct btrfs_block_rsv*,struct btrfs_block_rsv*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_fs_info*) ; 
 void* btrfs_calc_trans_metadata_size (struct btrfs_fs_info*,int) ; 
 int btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_free_block_rsv (struct btrfs_fs_info*,struct btrfs_block_rsv*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_fs_incompat (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_inode_sectorsize (struct inode*) ; 
 int btrfs_punch_hole_lock_range (struct inode*,scalar_t__,scalar_t__,struct extent_state**) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_truncate_block (struct inode*,scalar_t__,scalar_t__,int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int btrfs_wait_ordered_range (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int fill_holes (struct btrfs_trans_handle*,TYPE_1__*,struct btrfs_path*,scalar_t__,scalar_t__) ; 
 int find_first_non_hole (struct inode*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ round_down (scalar_t__,scalar_t__) ; 
 scalar_t__ round_up (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_extent_cached (int /*<<< orphan*/ *,scalar_t__,scalar_t__,struct extent_state**) ; 

__attribute__((used)) static int btrfs_punch_hole(struct inode *inode, loff_t offset, loff_t len)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct extent_state *cached_state = NULL;
	struct btrfs_path *path;
	struct btrfs_block_rsv *rsv;
	struct btrfs_trans_handle *trans;
	u64 lockstart;
	u64 lockend;
	u64 tail_start;
	u64 tail_len;
	u64 orig_start = offset;
	u64 cur_offset;
	u64 min_size = btrfs_calc_trans_metadata_size(fs_info, 1);
	u64 drop_end;
	int ret = 0;
	int err = 0;
	unsigned int rsv_count;
	bool same_block;
	bool no_holes = btrfs_fs_incompat(fs_info, NO_HOLES);
	u64 ino_size;
	bool truncated_block = false;
	bool updated_inode = false;

	ret = btrfs_wait_ordered_range(inode, offset, len);
	if (ret)
		return ret;

	inode_lock(inode);
	ino_size = round_up(inode->i_size, fs_info->sectorsize);
	ret = find_first_non_hole(inode, &offset, &len);
	if (ret < 0)
		goto out_only_mutex;
	if (ret && !len) {
		/* Already in a large hole */
		ret = 0;
		goto out_only_mutex;
	}

	lockstart = round_up(offset, btrfs_inode_sectorsize(inode));
	lockend = round_down(offset + len,
			     btrfs_inode_sectorsize(inode)) - 1;
	same_block = (BTRFS_BYTES_TO_BLKS(fs_info, offset))
		== (BTRFS_BYTES_TO_BLKS(fs_info, offset + len - 1));
	/*
	 * We needn't truncate any block which is beyond the end of the file
	 * because we are sure there is no data there.
	 */
	/*
	 * Only do this if we are in the same block and we aren't doing the
	 * entire block.
	 */
	if (same_block && len < fs_info->sectorsize) {
		if (offset < ino_size) {
			truncated_block = true;
			ret = btrfs_truncate_block(inode, offset, len, 0);
		} else {
			ret = 0;
		}
		goto out_only_mutex;
	}

	/* zero back part of the first block */
	if (offset < ino_size) {
		truncated_block = true;
		ret = btrfs_truncate_block(inode, offset, 0, 0);
		if (ret) {
			inode_unlock(inode);
			return ret;
		}
	}

	/* Check the aligned pages after the first unaligned page,
	 * if offset != orig_start, which means the first unaligned page
	 * including several following pages are already in holes,
	 * the extra check can be skipped */
	if (offset == orig_start) {
		/* after truncate page, check hole again */
		len = offset + len - lockstart;
		offset = lockstart;
		ret = find_first_non_hole(inode, &offset, &len);
		if (ret < 0)
			goto out_only_mutex;
		if (ret && !len) {
			ret = 0;
			goto out_only_mutex;
		}
		lockstart = offset;
	}

	/* Check the tail unaligned part is in a hole */
	tail_start = lockend + 1;
	tail_len = offset + len - tail_start;
	if (tail_len) {
		ret = find_first_non_hole(inode, &tail_start, &tail_len);
		if (unlikely(ret < 0))
			goto out_only_mutex;
		if (!ret) {
			/* zero the front end of the last page */
			if (tail_start + tail_len < ino_size) {
				truncated_block = true;
				ret = btrfs_truncate_block(inode,
							tail_start + tail_len,
							0, 1);
				if (ret)
					goto out_only_mutex;
			}
		}
	}

	if (lockend < lockstart) {
		ret = 0;
		goto out_only_mutex;
	}

	ret = btrfs_punch_hole_lock_range(inode, lockstart, lockend,
					  &cached_state);
	if (ret) {
		inode_unlock(inode);
		goto out_only_mutex;
	}

	path = btrfs_alloc_path();
	if (!path) {
		ret = -ENOMEM;
		goto out;
	}

	rsv = btrfs_alloc_block_rsv(fs_info, BTRFS_BLOCK_RSV_TEMP);
	if (!rsv) {
		ret = -ENOMEM;
		goto out_free;
	}
	rsv->size = btrfs_calc_trans_metadata_size(fs_info, 1);
	rsv->failfast = 1;

	/*
	 * 1 - update the inode
	 * 1 - removing the extents in the range
	 * 1 - adding the hole extent if no_holes isn't set
	 */
	rsv_count = no_holes ? 2 : 3;
	trans = btrfs_start_transaction(root, rsv_count);
	if (IS_ERR(trans)) {
		err = PTR_ERR(trans);
		goto out_free;
	}

	ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv, rsv,
				      min_size, 0);
	BUG_ON(ret);
	trans->block_rsv = rsv;

	cur_offset = lockstart;
	len = lockend - cur_offset;
	while (cur_offset < lockend) {
		ret = __btrfs_drop_extents(trans, root, inode, path,
					   cur_offset, lockend + 1,
					   &drop_end, 1, 0, 0, NULL);
		if (ret != -ENOSPC)
			break;

		trans->block_rsv = &fs_info->trans_block_rsv;

		if (cur_offset < drop_end && cur_offset < ino_size) {
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
				err = ret;
				break;
			}
		}

		cur_offset = drop_end;

		ret = btrfs_update_inode(trans, root, inode);
		if (ret) {
			err = ret;
			break;
		}

		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		trans = btrfs_start_transaction(root, rsv_count);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			trans = NULL;
			break;
		}

		ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv,
					      rsv, min_size, 0);
		BUG_ON(ret);	/* shouldn't happen */
		trans->block_rsv = rsv;

		ret = find_first_non_hole(inode, &cur_offset, &len);
		if (unlikely(ret < 0))
			break;
		if (ret && !len) {
			ret = 0;
			break;
		}
	}

	if (ret) {
		err = ret;
		goto out_trans;
	}

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
	if (drop_end <= lockend)
		drop_end = lockend + 1;
	/*
	 * Don't insert file hole extent item if it's for a range beyond eof
	 * (because it's useless) or if it represents a 0 bytes range (when
	 * cur_offset == drop_end).
	 */
	if (cur_offset < ino_size && cur_offset < drop_end) {
		ret = fill_holes(trans, BTRFS_I(inode), path,
				cur_offset, drop_end);
		if (ret) {
			/* Same comment as above. */
			btrfs_abort_transaction(trans, ret);
			err = ret;
			goto out_trans;
		}
	}

out_trans:
	if (!trans)
		goto out_free;

	inode_inc_iversion(inode);
	inode->i_mtime = inode->i_ctime = current_time(inode);

	trans->block_rsv = &fs_info->trans_block_rsv;
	ret = btrfs_update_inode(trans, root, inode);
	updated_inode = true;
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(fs_info);
out_free:
	btrfs_free_path(path);
	btrfs_free_block_rsv(fs_info, rsv);
out:
	unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart, lockend,
			     &cached_state);
out_only_mutex:
	if (!updated_inode && truncated_block && !ret && !err) {
		/*
		 * If we only end up zeroing part of a page, we still need to
		 * update the inode item, so that all the time fields are
		 * updated as well as the necessary btrfs inode in memory fields
		 * for detecting, at fsync time, if the inode isn't yet in the
		 * log tree or it's there but not up to date.
		 */
		trans = btrfs_start_transaction(root, 1);
		if (IS_ERR(trans)) {
			err = PTR_ERR(trans);
		} else {
			err = btrfs_update_inode(trans, root, inode);
			ret = btrfs_end_transaction(trans);
		}
	}
	inode_unlock(inode);
	if (ret && !err)
		err = ret;
	return err;
}