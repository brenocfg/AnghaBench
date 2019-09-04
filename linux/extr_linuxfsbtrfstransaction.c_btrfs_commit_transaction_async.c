#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct btrfs_transaction {int /*<<< orphan*/  use_count; } ;
struct btrfs_trans_handle {struct btrfs_transaction* transaction; int /*<<< orphan*/  root; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sb; } ;
struct btrfs_async_commit {int /*<<< orphan*/  work; TYPE_2__* newtrans; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_5__ {struct btrfs_trans_handle* journal_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SB_FREEZE_FS ; 
 int __TRANS_FREEZABLE ; 
 int /*<<< orphan*/  __sb_writers_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 TYPE_2__* btrfs_join_transaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_transaction (struct btrfs_transaction*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_async_commit ; 
 int /*<<< orphan*/  kfree (struct btrfs_async_commit*) ; 
 struct btrfs_async_commit* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_current_trans_commit_start (struct btrfs_fs_info*,struct btrfs_transaction*) ; 
 int /*<<< orphan*/  wait_current_trans_commit_start_and_unblock (struct btrfs_fs_info*,struct btrfs_transaction*) ; 

int btrfs_commit_transaction_async(struct btrfs_trans_handle *trans,
				   int wait_for_unblock)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_async_commit *ac;
	struct btrfs_transaction *cur_trans;

	ac = kmalloc(sizeof(*ac), GFP_NOFS);
	if (!ac)
		return -ENOMEM;

	INIT_WORK(&ac->work, do_async_commit);
	ac->newtrans = btrfs_join_transaction(trans->root);
	if (IS_ERR(ac->newtrans)) {
		int err = PTR_ERR(ac->newtrans);
		kfree(ac);
		return err;
	}

	/* take transaction reference */
	cur_trans = trans->transaction;
	refcount_inc(&cur_trans->use_count);

	btrfs_end_transaction(trans);

	/*
	 * Tell lockdep we've released the freeze rwsem, since the
	 * async commit thread will be the one to unlock it.
	 */
	if (ac->newtrans->type & __TRANS_FREEZABLE)
		__sb_writers_release(fs_info->sb, SB_FREEZE_FS);

	schedule_work(&ac->work);

	/* wait for transaction to start and unblock */
	if (wait_for_unblock)
		wait_current_trans_commit_start_and_unblock(fs_info, cur_trans);
	else
		wait_current_trans_commit_start(fs_info, cur_trans);

	if (current->journal_info == trans)
		current->journal_info = NULL;

	btrfs_put_transaction(cur_trans);
	return 0;
}