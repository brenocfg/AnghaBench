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
struct workspace {int req_level; int level; int /*<<< orphan*/  list; int /*<<< orphan*/  lru_list; scalar_t__ last_used; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/ * idle_ws; int /*<<< orphan*/  active_map; int /*<<< orphan*/  timer; int /*<<< orphan*/  lru_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ZSTD_BTRFS_MAX_LEVEL ; 
 scalar_t__ ZSTD_BTRFS_RECLAIM_JIFFIES ; 
 int /*<<< orphan*/  cond_wake_up (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct workspace* list_to_workspace (struct list_head*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 TYPE_1__ wsm ; 

__attribute__((used)) static void zstd_put_workspace(struct list_head *ws)
{
	struct workspace *workspace = list_to_workspace(ws);

	spin_lock_bh(&wsm.lock);

	/* A node is only taken off the lru if we are the corresponding level */
	if (workspace->req_level == workspace->level) {
		/* Hide a max level workspace from reclaim */
		if (list_empty(&wsm.idle_ws[ZSTD_BTRFS_MAX_LEVEL - 1])) {
			INIT_LIST_HEAD(&workspace->lru_list);
		} else {
			workspace->last_used = jiffies;
			list_add(&workspace->lru_list, &wsm.lru_list);
			if (!timer_pending(&wsm.timer))
				mod_timer(&wsm.timer,
					  jiffies + ZSTD_BTRFS_RECLAIM_JIFFIES);
		}
	}

	set_bit(workspace->level - 1, &wsm.active_map);
	list_add(&workspace->list, &wsm.idle_ws[workspace->level - 1]);
	workspace->req_level = 0;

	spin_unlock_bh(&wsm.lock);

	if (workspace->level == ZSTD_BTRFS_MAX_LEVEL)
		cond_wake_up(&wsm.wait);
}