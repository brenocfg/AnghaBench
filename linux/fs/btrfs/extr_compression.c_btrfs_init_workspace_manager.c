#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct workspace_manager {int free_ws; int /*<<< orphan*/  idle_ws; int /*<<< orphan*/  total_ws; struct btrfs_compress_op const* ops; int /*<<< orphan*/  ws_wait; int /*<<< orphan*/  ws_lock; } ;
struct list_head {int dummy; } ;
struct btrfs_compress_op {struct list_head* (* alloc_workspace ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct list_head*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct list_head* stub1 (int /*<<< orphan*/ ) ; 

void btrfs_init_workspace_manager(struct workspace_manager *wsm,
				  const struct btrfs_compress_op *ops)
{
	struct list_head *workspace;

	wsm->ops = ops;

	INIT_LIST_HEAD(&wsm->idle_ws);
	spin_lock_init(&wsm->ws_lock);
	atomic_set(&wsm->total_ws, 0);
	init_waitqueue_head(&wsm->ws_wait);

	/*
	 * Preallocate one workspace for each compression type so we can
	 * guarantee forward progress in the worst case
	 */
	workspace = wsm->ops->alloc_workspace(0);
	if (IS_ERR(workspace)) {
		pr_warn(
	"BTRFS: cannot preallocate compression workspace, will try later\n");
	} else {
		atomic_set(&wsm->total_ws, 1);
		wsm->free_ws = 1;
		list_add(workspace, &wsm->idle_ws);
	}
}