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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root_item {int dummy; } ;
struct btrfs_root {int log_transid_committed; int log_transid; int last_log_commit; int /*<<< orphan*/ * log_commit_wait; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/ * log_commit; TYPE_1__* node; int /*<<< orphan*/  dirty_log_pages; int /*<<< orphan*/  log_writer_wait; int /*<<< orphan*/  log_writers; int /*<<< orphan*/ * log_ctxs; int /*<<< orphan*/  log_batch; scalar_t__ log_start_pid; int /*<<< orphan*/  root_item; int /*<<< orphan*/  state; struct btrfs_root* log_root; struct btrfs_fs_info* fs_info; } ;
struct btrfs_log_ctx {int log_transid; int log_ret; int /*<<< orphan*/  list; } ;
struct btrfs_fs_info {int /*<<< orphan*/  super_for_commit; struct btrfs_root* log_root_tree; } ;
struct blk_plug {int dummy; } ;
typedef  int /*<<< orphan*/  new_root_item ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTRFS_ROOT_MULTI_LOG_TASKS ; 
 int EAGAIN ; 
 int ENOSPC ; 
 int EXTENT_DIRTY ; 
 int EXTENT_NEW ; 
 int /*<<< orphan*/  SSD ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int /*<<< orphan*/  btrfs_header_level (TYPE_1__*) ; 
 int /*<<< orphan*/  btrfs_init_log_ctx (struct btrfs_log_ctx*,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_need_log_full_commit (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_remove_all_log_ctxs (struct btrfs_root*,int,int) ; 
 int /*<<< orphan*/  btrfs_set_log_full_commit (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_set_root_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  btrfs_set_super_log_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_super_log_root_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int btrfs_wait_tree_log_extents (struct btrfs_root*,int) ; 
 int btrfs_write_marked_extents (struct btrfs_fs_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cond_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_wake_up_nomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_root_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int update_log_root (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_root_item*) ; 
 int /*<<< orphan*/  wait_for_writer (struct btrfs_root*) ; 
 int /*<<< orphan*/  wait_log_commit (struct btrfs_root*,int) ; 
 int write_all_supers (struct btrfs_fs_info*,int) ; 

int btrfs_sync_log(struct btrfs_trans_handle *trans,
		   struct btrfs_root *root, struct btrfs_log_ctx *ctx)
{
	int index1;
	int index2;
	int mark;
	int ret;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_root *log = root->log_root;
	struct btrfs_root *log_root_tree = fs_info->log_root_tree;
	struct btrfs_root_item new_root_item;
	int log_transid = 0;
	struct btrfs_log_ctx root_log_ctx;
	struct blk_plug plug;

	mutex_lock(&root->log_mutex);
	log_transid = ctx->log_transid;
	if (root->log_transid_committed >= log_transid) {
		mutex_unlock(&root->log_mutex);
		return ctx->log_ret;
	}

	index1 = log_transid % 2;
	if (atomic_read(&root->log_commit[index1])) {
		wait_log_commit(root, log_transid);
		mutex_unlock(&root->log_mutex);
		return ctx->log_ret;
	}
	ASSERT(log_transid == root->log_transid);
	atomic_set(&root->log_commit[index1], 1);

	/* wait for previous tree log sync to complete */
	if (atomic_read(&root->log_commit[(index1 + 1) % 2]))
		wait_log_commit(root, log_transid - 1);

	while (1) {
		int batch = atomic_read(&root->log_batch);
		/* when we're on an ssd, just kick the log commit out */
		if (!btrfs_test_opt(fs_info, SSD) &&
		    test_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state)) {
			mutex_unlock(&root->log_mutex);
			schedule_timeout_uninterruptible(1);
			mutex_lock(&root->log_mutex);
		}
		wait_for_writer(root);
		if (batch == atomic_read(&root->log_batch))
			break;
	}

	/* bail out if we need to do a full commit */
	if (btrfs_need_log_full_commit(trans)) {
		ret = -EAGAIN;
		mutex_unlock(&root->log_mutex);
		goto out;
	}

	if (log_transid % 2 == 0)
		mark = EXTENT_DIRTY;
	else
		mark = EXTENT_NEW;

	/* we start IO on  all the marked extents here, but we don't actually
	 * wait for them until later.
	 */
	blk_start_plug(&plug);
	ret = btrfs_write_marked_extents(fs_info, &log->dirty_log_pages, mark);
	if (ret) {
		blk_finish_plug(&plug);
		btrfs_abort_transaction(trans, ret);
		btrfs_set_log_full_commit(trans);
		mutex_unlock(&root->log_mutex);
		goto out;
	}

	/*
	 * We _must_ update under the root->log_mutex in order to make sure we
	 * have a consistent view of the log root we are trying to commit at
	 * this moment.
	 *
	 * We _must_ copy this into a local copy, because we are not holding the
	 * log_root_tree->log_mutex yet.  This is important because when we
	 * commit the log_root_tree we must have a consistent view of the
	 * log_root_tree when we update the super block to point at the
	 * log_root_tree bytenr.  If we update the log_root_tree here we'll race
	 * with the commit and possibly point at the new block which we may not
	 * have written out.
	 */
	btrfs_set_root_node(&log->root_item, log->node);
	memcpy(&new_root_item, &log->root_item, sizeof(new_root_item));

	root->log_transid++;
	log->log_transid = root->log_transid;
	root->log_start_pid = 0;
	/*
	 * IO has been started, blocks of the log tree have WRITTEN flag set
	 * in their headers. new modifications of the log will be written to
	 * new positions. so it's safe to allow log writers to go in.
	 */
	mutex_unlock(&root->log_mutex);

	btrfs_init_log_ctx(&root_log_ctx, NULL);

	mutex_lock(&log_root_tree->log_mutex);
	atomic_inc(&log_root_tree->log_batch);
	atomic_inc(&log_root_tree->log_writers);

	index2 = log_root_tree->log_transid % 2;
	list_add_tail(&root_log_ctx.list, &log_root_tree->log_ctxs[index2]);
	root_log_ctx.log_transid = log_root_tree->log_transid;

	mutex_unlock(&log_root_tree->log_mutex);

	mutex_lock(&log_root_tree->log_mutex);

	/*
	 * Now we are safe to update the log_root_tree because we're under the
	 * log_mutex, and we're a current writer so we're holding the commit
	 * open until we drop the log_mutex.
	 */
	ret = update_log_root(trans, log, &new_root_item);

	if (atomic_dec_and_test(&log_root_tree->log_writers)) {
		/* atomic_dec_and_test implies a barrier */
		cond_wake_up_nomb(&log_root_tree->log_writer_wait);
	}

	if (ret) {
		if (!list_empty(&root_log_ctx.list))
			list_del_init(&root_log_ctx.list);

		blk_finish_plug(&plug);
		btrfs_set_log_full_commit(trans);

		if (ret != -ENOSPC) {
			btrfs_abort_transaction(trans, ret);
			mutex_unlock(&log_root_tree->log_mutex);
			goto out;
		}
		btrfs_wait_tree_log_extents(log, mark);
		mutex_unlock(&log_root_tree->log_mutex);
		ret = -EAGAIN;
		goto out;
	}

	if (log_root_tree->log_transid_committed >= root_log_ctx.log_transid) {
		blk_finish_plug(&plug);
		list_del_init(&root_log_ctx.list);
		mutex_unlock(&log_root_tree->log_mutex);
		ret = root_log_ctx.log_ret;
		goto out;
	}

	index2 = root_log_ctx.log_transid % 2;
	if (atomic_read(&log_root_tree->log_commit[index2])) {
		blk_finish_plug(&plug);
		ret = btrfs_wait_tree_log_extents(log, mark);
		wait_log_commit(log_root_tree,
				root_log_ctx.log_transid);
		mutex_unlock(&log_root_tree->log_mutex);
		if (!ret)
			ret = root_log_ctx.log_ret;
		goto out;
	}
	ASSERT(root_log_ctx.log_transid == log_root_tree->log_transid);
	atomic_set(&log_root_tree->log_commit[index2], 1);

	if (atomic_read(&log_root_tree->log_commit[(index2 + 1) % 2])) {
		wait_log_commit(log_root_tree,
				root_log_ctx.log_transid - 1);
	}

	wait_for_writer(log_root_tree);

	/*
	 * now that we've moved on to the tree of log tree roots,
	 * check the full commit flag again
	 */
	if (btrfs_need_log_full_commit(trans)) {
		blk_finish_plug(&plug);
		btrfs_wait_tree_log_extents(log, mark);
		mutex_unlock(&log_root_tree->log_mutex);
		ret = -EAGAIN;
		goto out_wake_log_root;
	}

	ret = btrfs_write_marked_extents(fs_info,
					 &log_root_tree->dirty_log_pages,
					 EXTENT_DIRTY | EXTENT_NEW);
	blk_finish_plug(&plug);
	if (ret) {
		btrfs_set_log_full_commit(trans);
		btrfs_abort_transaction(trans, ret);
		mutex_unlock(&log_root_tree->log_mutex);
		goto out_wake_log_root;
	}
	ret = btrfs_wait_tree_log_extents(log, mark);
	if (!ret)
		ret = btrfs_wait_tree_log_extents(log_root_tree,
						  EXTENT_NEW | EXTENT_DIRTY);
	if (ret) {
		btrfs_set_log_full_commit(trans);
		mutex_unlock(&log_root_tree->log_mutex);
		goto out_wake_log_root;
	}

	btrfs_set_super_log_root(fs_info->super_for_commit,
				 log_root_tree->node->start);
	btrfs_set_super_log_root_level(fs_info->super_for_commit,
				       btrfs_header_level(log_root_tree->node));

	log_root_tree->log_transid++;
	mutex_unlock(&log_root_tree->log_mutex);

	/*
	 * Nobody else is going to jump in and write the ctree
	 * super here because the log_commit atomic below is protecting
	 * us.  We must be called with a transaction handle pinning
	 * the running transaction open, so a full commit can't hop
	 * in and cause problems either.
	 */
	ret = write_all_supers(fs_info, 1);
	if (ret) {
		btrfs_set_log_full_commit(trans);
		btrfs_abort_transaction(trans, ret);
		goto out_wake_log_root;
	}

	mutex_lock(&root->log_mutex);
	if (root->last_log_commit < log_transid)
		root->last_log_commit = log_transid;
	mutex_unlock(&root->log_mutex);

out_wake_log_root:
	mutex_lock(&log_root_tree->log_mutex);
	btrfs_remove_all_log_ctxs(log_root_tree, index2, ret);

	log_root_tree->log_transid_committed++;
	atomic_set(&log_root_tree->log_commit[index2], 0);
	mutex_unlock(&log_root_tree->log_mutex);

	/*
	 * The barrier before waitqueue_active (in cond_wake_up) is needed so
	 * all the updates above are seen by the woken threads. It might not be
	 * necessary, but proving that seems to be hard.
	 */
	cond_wake_up(&log_root_tree->log_commit_wait[index2]);
out:
	mutex_lock(&root->log_mutex);
	btrfs_remove_all_log_ctxs(root, index1, ret);
	root->log_transid_committed++;
	atomic_set(&root->log_commit[index1], 0);
	mutex_unlock(&root->log_mutex);

	/*
	 * The barrier before waitqueue_active (in cond_wake_up) is needed so
	 * all the updates above are seen by the woken threads. It might not be
	 * necessary, but proving that seems to be hard.
	 */
	cond_wake_up(&root->log_commit_wait[index1]);
	return ret;
}