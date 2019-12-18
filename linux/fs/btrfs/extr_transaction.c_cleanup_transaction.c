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
struct btrfs_transaction {int /*<<< orphan*/  num_writers; int /*<<< orphan*/  writer_wait; int /*<<< orphan*/  state; int /*<<< orphan*/  list; } ;
struct btrfs_trans_handle {int type; int /*<<< orphan*/  root; struct btrfs_transaction* transaction; int /*<<< orphan*/  use_count; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sb; int /*<<< orphan*/  trans_lock; struct btrfs_transaction* running_transaction; } ;
struct TYPE_2__ {struct btrfs_trans_handle* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_STATE_COMMIT_DOING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __TRANS_FREEZABLE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int /*<<< orphan*/  btrfs_cleanup_one_transaction (struct btrfs_transaction*,struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  btrfs_scrub_cancel (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_trans_handle_cachep ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cleanup_transaction(struct btrfs_trans_handle *trans, int err)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_transaction *cur_trans = trans->transaction;

	WARN_ON(refcount_read(&trans->use_count) > 1);

	btrfs_abort_transaction(trans, err);

	spin_lock(&fs_info->trans_lock);

	/*
	 * If the transaction is removed from the list, it means this
	 * transaction has been committed successfully, so it is impossible
	 * to call the cleanup function.
	 */
	BUG_ON(list_empty(&cur_trans->list));

	list_del_init(&cur_trans->list);
	if (cur_trans == fs_info->running_transaction) {
		cur_trans->state = TRANS_STATE_COMMIT_DOING;
		spin_unlock(&fs_info->trans_lock);
		wait_event(cur_trans->writer_wait,
			   atomic_read(&cur_trans->num_writers) == 1);

		spin_lock(&fs_info->trans_lock);
	}
	spin_unlock(&fs_info->trans_lock);

	btrfs_cleanup_one_transaction(trans->transaction, fs_info);

	spin_lock(&fs_info->trans_lock);
	if (cur_trans == fs_info->running_transaction)
		fs_info->running_transaction = NULL;
	spin_unlock(&fs_info->trans_lock);

	if (trans->type & __TRANS_FREEZABLE)
		sb_end_intwrite(fs_info->sb);
	btrfs_put_transaction(cur_trans);
	btrfs_put_transaction(cur_trans);

	trace_btrfs_transaction_commit(trans->root);

	if (current->journal_info == trans)
		current->journal_info = NULL;
	btrfs_scrub_cancel(fs_info);

	kmem_cache_free(btrfs_trans_handle_cachep, trans);
}