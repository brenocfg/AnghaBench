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
typedef  int u64 ;
struct inode {int i_size; int /*<<< orphan*/  i_sb; } ;
struct btrfs_trans_handle {struct btrfs_block_rsv* block_rsv; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_block_rsv {int size; int failfast; } ;
struct btrfs_fs_info {int sectorsize; struct btrfs_block_rsv trans_block_rsv; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_RSV_TEMP ; 
 int /*<<< orphan*/  BTRFS_EXTENT_DATA_KEY ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_NEEDS_FULL_SYNC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int NEED_TRUNCATE_BLOCK ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 struct btrfs_block_rsv* btrfs_alloc_block_rsv (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfs_block_rsv_migrate (struct btrfs_block_rsv*,struct btrfs_block_rsv*,int,int) ; 
 int /*<<< orphan*/  btrfs_block_rsv_release (struct btrfs_fs_info*,struct btrfs_block_rsv*,int) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_fs_info*) ; 
 int btrfs_calc_metadata_size (struct btrfs_fs_info*,int) ; 
 int btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_free_block_rsv (struct btrfs_fs_info*,struct btrfs_block_rsv*) ; 
 int /*<<< orphan*/  btrfs_ordered_update_i_size (struct inode*,int,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_truncate_block (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_truncate_inode_items (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int,int /*<<< orphan*/ ) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int btrfs_wait_ordered_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_truncate(struct inode *inode, bool skip_writeback)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_block_rsv *rsv;
	int ret;
	struct btrfs_trans_handle *trans;
	u64 mask = fs_info->sectorsize - 1;
	u64 min_size = btrfs_calc_metadata_size(fs_info, 1);

	if (!skip_writeback) {
		ret = btrfs_wait_ordered_range(inode, inode->i_size & (~mask),
					       (u64)-1);
		if (ret)
			return ret;
	}

	/*
	 * Yes ladies and gentlemen, this is indeed ugly.  We have a couple of
	 * things going on here:
	 *
	 * 1) We need to reserve space to update our inode.
	 *
	 * 2) We need to have something to cache all the space that is going to
	 * be free'd up by the truncate operation, but also have some slack
	 * space reserved in case it uses space during the truncate (thank you
	 * very much snapshotting).
	 *
	 * And we need these to be separate.  The fact is we can use a lot of
	 * space doing the truncate, and we have no earthly idea how much space
	 * we will use, so we need the truncate reservation to be separate so it
	 * doesn't end up using space reserved for updating the inode.  We also
	 * need to be able to stop the transaction and start a new one, which
	 * means we need to be able to update the inode several times, and we
	 * have no idea of knowing how many times that will be, so we can't just
	 * reserve 1 item for the entirety of the operation, so that has to be
	 * done separately as well.
	 *
	 * So that leaves us with
	 *
	 * 1) rsv - for the truncate reservation, which we will steal from the
	 * transaction reservation.
	 * 2) fs_info->trans_block_rsv - this will have 1 items worth left for
	 * updating the inode.
	 */
	rsv = btrfs_alloc_block_rsv(fs_info, BTRFS_BLOCK_RSV_TEMP);
	if (!rsv)
		return -ENOMEM;
	rsv->size = min_size;
	rsv->failfast = 1;

	/*
	 * 1 for the truncate slack space
	 * 1 for updating the inode.
	 */
	trans = btrfs_start_transaction(root, 2);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		goto out;
	}

	/* Migrate the slack space for the truncate to our reserve */
	ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv, rsv,
				      min_size, false);
	BUG_ON(ret);

	/*
	 * So if we truncate and then write and fsync we normally would just
	 * write the extents that changed, which is a problem if we need to
	 * first truncate that entire inode.  So set this flag so we write out
	 * all of the extents in the inode to the sync log so we're completely
	 * safe.
	 */
	set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &BTRFS_I(inode)->runtime_flags);
	trans->block_rsv = rsv;

	while (1) {
		ret = btrfs_truncate_inode_items(trans, root, inode,
						 inode->i_size,
						 BTRFS_EXTENT_DATA_KEY);
		trans->block_rsv = &fs_info->trans_block_rsv;
		if (ret != -ENOSPC && ret != -EAGAIN)
			break;

		ret = btrfs_update_inode(trans, root, inode);
		if (ret)
			break;

		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		trans = btrfs_start_transaction(root, 2);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			trans = NULL;
			break;
		}

		btrfs_block_rsv_release(fs_info, rsv, -1);
		ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv,
					      rsv, min_size, false);
		BUG_ON(ret);	/* shouldn't happen */
		trans->block_rsv = rsv;
	}

	/*
	 * We can't call btrfs_truncate_block inside a trans handle as we could
	 * deadlock with freeze, if we got NEED_TRUNCATE_BLOCK then we know
	 * we've truncated everything except the last little bit, and can do
	 * btrfs_truncate_block and then update the disk_i_size.
	 */
	if (ret == NEED_TRUNCATE_BLOCK) {
		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		ret = btrfs_truncate_block(inode, inode->i_size, 0, 0);
		if (ret)
			goto out;
		trans = btrfs_start_transaction(root, 1);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			goto out;
		}
		btrfs_ordered_update_i_size(inode, inode->i_size, NULL);
	}

	if (trans) {
		int ret2;

		trans->block_rsv = &fs_info->trans_block_rsv;
		ret2 = btrfs_update_inode(trans, root, inode);
		if (ret2 && !ret)
			ret = ret2;

		ret2 = btrfs_end_transaction(trans);
		if (ret2 && !ret)
			ret = ret2;
		btrfs_btree_balance_dirty(fs_info);
	}
out:
	btrfs_free_block_rsv(fs_info, rsv);

	return ret;
}