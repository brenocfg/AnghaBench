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
struct btrfs_transaction {int /*<<< orphan*/  writer_wait; int /*<<< orphan*/  num_writers; int /*<<< orphan*/  state; } ;
struct btrfs_trans_handle {int type; scalar_t__ aborted; int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/ * orig_rsv; int /*<<< orphan*/  use_count; struct btrfs_transaction* transaction; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  transaction_kthread; int /*<<< orphan*/  fs_state; struct btrfs_transaction* running_transaction; int /*<<< orphan*/  sb; } ;
struct TYPE_2__ {struct btrfs_trans_handle* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_STATE_ERROR ; 
 int EIO ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int TRANS_JOIN_NOLOCK ; 
 scalar_t__ TRANS_STATE_BLOCKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __TRANS_FREEZABLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_create_pending_block_groups (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_iputs (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_trans_handle_cachep ; 
 int /*<<< orphan*/  btrfs_trans_release_chunk_metadata (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_trans_release_metadata (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  cond_wake_up (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  extwriter_counter_dec (struct btrfs_transaction*,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __btrfs_end_transaction(struct btrfs_trans_handle *trans,
				   int throttle)
{
	struct btrfs_fs_info *info = trans->fs_info;
	struct btrfs_transaction *cur_trans = trans->transaction;
	int lock = (trans->type != TRANS_JOIN_NOLOCK);
	int err = 0;

	if (refcount_read(&trans->use_count) > 1) {
		refcount_dec(&trans->use_count);
		trans->block_rsv = trans->orig_rsv;
		return 0;
	}

	btrfs_trans_release_metadata(trans);
	trans->block_rsv = NULL;

	btrfs_create_pending_block_groups(trans);

	btrfs_trans_release_chunk_metadata(trans);

	if (lock && READ_ONCE(cur_trans->state) == TRANS_STATE_BLOCKED) {
		if (throttle)
			return btrfs_commit_transaction(trans);
		else
			wake_up_process(info->transaction_kthread);
	}

	if (trans->type & __TRANS_FREEZABLE)
		sb_end_intwrite(info->sb);

	WARN_ON(cur_trans != info->running_transaction);
	WARN_ON(atomic_read(&cur_trans->num_writers) < 1);
	atomic_dec(&cur_trans->num_writers);
	extwriter_counter_dec(cur_trans, trans->type);

	cond_wake_up(&cur_trans->writer_wait);
	btrfs_put_transaction(cur_trans);

	if (current->journal_info == trans)
		current->journal_info = NULL;

	if (throttle)
		btrfs_run_delayed_iputs(info);

	if (trans->aborted ||
	    test_bit(BTRFS_FS_STATE_ERROR, &info->fs_state)) {
		wake_up_process(info->transaction_kthread);
		err = -EIO;
	}

	kmem_cache_free(btrfs_trans_handle_cachep, trans);
	return err;
}