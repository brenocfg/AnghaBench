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
struct btrfs_transaction {scalar_t__ state; int /*<<< orphan*/  transid; } ;
struct btrfs_trans_handle {unsigned int type; int can_flush_pending_bgs; int bytes_reserved; int reloc_reserved; struct btrfs_block_rsv* block_rsv; int /*<<< orphan*/  transid; int /*<<< orphan*/  new_bgs; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  use_count; struct btrfs_root* root; struct btrfs_transaction* transaction; struct btrfs_block_rsv* orig_rsv; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_block_rsv {scalar_t__ full; } ;
struct btrfs_fs_info {unsigned int nodesize; struct btrfs_block_rsv trans_block_rsv; int /*<<< orphan*/  sb; struct btrfs_transaction* running_transaction; struct btrfs_root* chunk_root; int /*<<< orphan*/  fs_state; struct btrfs_block_rsv delayed_refs_rsv; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;
struct TYPE_2__ {struct btrfs_trans_handle* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTRFS_FS_STATE_ERROR ; 
 int BTRFS_RESERVE_FLUSH_ALL ; 
 struct btrfs_trans_handle* BTRFS_SEND_TRANS_STUB ; 
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EROFS ; 
 struct btrfs_trans_handle* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int TRANS_ATTACH ; 
 unsigned int TRANS_EXTWRITERS ; 
 unsigned int TRANS_JOIN_NOSTART ; 
 scalar_t__ TRANS_STATE_BLOCKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int __TRANS_FREEZABLE ; 
 int btrfs_block_rsv_add (struct btrfs_root*,struct btrfs_block_rsv*,int,int) ; 
 int /*<<< orphan*/  btrfs_block_rsv_release (struct btrfs_fs_info*,struct btrfs_block_rsv*,int) ; 
 int btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,unsigned int) ; 
 int /*<<< orphan*/  btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 int btrfs_delayed_refs_rsv_refill (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  btrfs_migrate_to_delayed_refs_rsv (struct btrfs_fs_info*,struct btrfs_block_rsv*,int) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_meta_pertrans (struct btrfs_root*,int) ; 
 int btrfs_qgroup_reserve_meta_pertrans (struct btrfs_root*,int,int) ; 
 int /*<<< orphan*/  btrfs_record_root_in_trans (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_trans_handle_cachep ; 
 TYPE_1__* current ; 
 int join_transaction (struct btrfs_fs_info*,unsigned int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ may_wait_transaction (struct btrfs_fs_info*,unsigned int) ; 
 scalar_t__ need_reserve_reloc_root (struct btrfs_root*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_current_trans (struct btrfs_fs_info*) ; 

__attribute__((used)) static struct btrfs_trans_handle *
start_transaction(struct btrfs_root *root, unsigned int num_items,
		  unsigned int type, enum btrfs_reserve_flush_enum flush,
		  bool enforce_qgroups)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_block_rsv *delayed_refs_rsv = &fs_info->delayed_refs_rsv;
	struct btrfs_trans_handle *h;
	struct btrfs_transaction *cur_trans;
	u64 num_bytes = 0;
	u64 qgroup_reserved = 0;
	bool reloc_reserved = false;
	int ret;

	/* Send isn't supposed to start transactions. */
	ASSERT(current->journal_info != BTRFS_SEND_TRANS_STUB);

	if (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		return ERR_PTR(-EROFS);

	if (current->journal_info) {
		WARN_ON(type & TRANS_EXTWRITERS);
		h = current->journal_info;
		refcount_inc(&h->use_count);
		WARN_ON(refcount_read(&h->use_count) > 2);
		h->orig_rsv = h->block_rsv;
		h->block_rsv = NULL;
		goto got_it;
	}

	/*
	 * Do the reservation before we join the transaction so we can do all
	 * the appropriate flushing if need be.
	 */
	if (num_items && root != fs_info->chunk_root) {
		struct btrfs_block_rsv *rsv = &fs_info->trans_block_rsv;
		u64 delayed_refs_bytes = 0;

		qgroup_reserved = num_items * fs_info->nodesize;
		ret = btrfs_qgroup_reserve_meta_pertrans(root, qgroup_reserved,
				enforce_qgroups);
		if (ret)
			return ERR_PTR(ret);

		/*
		 * We want to reserve all the bytes we may need all at once, so
		 * we only do 1 enospc flushing cycle per transaction start.  We
		 * accomplish this by simply assuming we'll do 2 x num_items
		 * worth of delayed refs updates in this trans handle, and
		 * refill that amount for whatever is missing in the reserve.
		 */
		num_bytes = btrfs_calc_insert_metadata_size(fs_info, num_items);
		if (delayed_refs_rsv->full == 0) {
			delayed_refs_bytes = num_bytes;
			num_bytes <<= 1;
		}

		/*
		 * Do the reservation for the relocation root creation
		 */
		if (need_reserve_reloc_root(root)) {
			num_bytes += fs_info->nodesize;
			reloc_reserved = true;
		}

		ret = btrfs_block_rsv_add(root, rsv, num_bytes, flush);
		if (ret)
			goto reserve_fail;
		if (delayed_refs_bytes) {
			btrfs_migrate_to_delayed_refs_rsv(fs_info, rsv,
							  delayed_refs_bytes);
			num_bytes -= delayed_refs_bytes;
		}
	} else if (num_items == 0 && flush == BTRFS_RESERVE_FLUSH_ALL &&
		   !delayed_refs_rsv->full) {
		/*
		 * Some people call with btrfs_start_transaction(root, 0)
		 * because they can be throttled, but have some other mechanism
		 * for reserving space.  We still want these guys to refill the
		 * delayed block_rsv so just add 1 items worth of reservation
		 * here.
		 */
		ret = btrfs_delayed_refs_rsv_refill(fs_info, flush);
		if (ret)
			goto reserve_fail;
	}
again:
	h = kmem_cache_zalloc(btrfs_trans_handle_cachep, GFP_NOFS);
	if (!h) {
		ret = -ENOMEM;
		goto alloc_fail;
	}

	/*
	 * If we are JOIN_NOLOCK we're already committing a transaction and
	 * waiting on this guy, so we don't need to do the sb_start_intwrite
	 * because we're already holding a ref.  We need this because we could
	 * have raced in and did an fsync() on a file which can kick a commit
	 * and then we deadlock with somebody doing a freeze.
	 *
	 * If we are ATTACH, it means we just want to catch the current
	 * transaction and commit it, so we needn't do sb_start_intwrite(). 
	 */
	if (type & __TRANS_FREEZABLE)
		sb_start_intwrite(fs_info->sb);

	if (may_wait_transaction(fs_info, type))
		wait_current_trans(fs_info);

	do {
		ret = join_transaction(fs_info, type);
		if (ret == -EBUSY) {
			wait_current_trans(fs_info);
			if (unlikely(type == TRANS_ATTACH ||
				     type == TRANS_JOIN_NOSTART))
				ret = -ENOENT;
		}
	} while (ret == -EBUSY);

	if (ret < 0)
		goto join_fail;

	cur_trans = fs_info->running_transaction;

	h->transid = cur_trans->transid;
	h->transaction = cur_trans;
	h->root = root;
	refcount_set(&h->use_count, 1);
	h->fs_info = root->fs_info;

	h->type = type;
	h->can_flush_pending_bgs = true;
	INIT_LIST_HEAD(&h->new_bgs);

	smp_mb();
	if (cur_trans->state >= TRANS_STATE_BLOCKED &&
	    may_wait_transaction(fs_info, type)) {
		current->journal_info = h;
		btrfs_commit_transaction(h);
		goto again;
	}

	if (num_bytes) {
		trace_btrfs_space_reservation(fs_info, "transaction",
					      h->transid, num_bytes, 1);
		h->block_rsv = &fs_info->trans_block_rsv;
		h->bytes_reserved = num_bytes;
		h->reloc_reserved = reloc_reserved;
	}

got_it:
	btrfs_record_root_in_trans(h, root);

	if (!current->journal_info)
		current->journal_info = h;
	return h;

join_fail:
	if (type & __TRANS_FREEZABLE)
		sb_end_intwrite(fs_info->sb);
	kmem_cache_free(btrfs_trans_handle_cachep, h);
alloc_fail:
	if (num_bytes)
		btrfs_block_rsv_release(fs_info, &fs_info->trans_block_rsv,
					num_bytes);
reserve_fail:
	btrfs_qgroup_free_meta_pertrans(root, qgroup_reserved);
	return ERR_PTR(ret);
}