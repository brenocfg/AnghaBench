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
struct btrfs_work {int dummy; } ;
struct btrfs_trans_handle {int sync; scalar_t__ transid; } ;
struct btrfs_fs_info {int dummy; } ;
struct async_delayed_refs {int error; scalar_t__ transid; int /*<<< orphan*/  wait; scalar_t__ sync; int /*<<< orphan*/  count; TYPE_1__* root; } ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (TYPE_1__*) ; 
 int btrfs_run_delayed_refs (struct btrfs_trans_handle*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_transaction_blocked (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct async_delayed_refs*) ; 
 struct async_delayed_refs* to_async_delayed_refs (struct btrfs_work*) ; 

__attribute__((used)) static void delayed_ref_async_start(struct btrfs_work *work)
{
	struct async_delayed_refs *async = to_async_delayed_refs(work);
	struct btrfs_trans_handle *trans;
	struct btrfs_fs_info *fs_info = async->root->fs_info;
	int ret;

	/* if the commit is already started, we don't need to wait here */
	if (btrfs_transaction_blocked(fs_info))
		goto done;

	trans = btrfs_join_transaction(async->root);
	if (IS_ERR(trans)) {
		async->error = PTR_ERR(trans);
		goto done;
	}

	/*
	 * trans->sync means that when we call end_transaction, we won't
	 * wait on delayed refs
	 */
	trans->sync = true;

	/* Don't bother flushing if we got into a different transaction */
	if (trans->transid > async->transid)
		goto end;

	ret = btrfs_run_delayed_refs(trans, async->count);
	if (ret)
		async->error = ret;
end:
	ret = btrfs_end_transaction(trans);
	if (ret && !async->error)
		async->error = ret;
done:
	if (async->sync)
		complete(&async->wait);
	else
		kfree(async);
}