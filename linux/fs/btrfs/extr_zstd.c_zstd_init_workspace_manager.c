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
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * idle_ws; int /*<<< orphan*/  active_map; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  timer; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct list_head*) ; 
 int ZSTD_BTRFS_MAX_LEVEL ; 
 int /*<<< orphan*/  btrfs_zstd_compress ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ wsm ; 
 struct list_head* zstd_alloc_workspace (int) ; 
 int /*<<< orphan*/  zstd_calc_ws_mem_sizes () ; 
 int /*<<< orphan*/  zstd_reclaim_timer_fn ; 

__attribute__((used)) static void zstd_init_workspace_manager(void)
{
	struct list_head *ws;
	int i;

	zstd_calc_ws_mem_sizes();

	wsm.ops = &btrfs_zstd_compress;
	spin_lock_init(&wsm.lock);
	init_waitqueue_head(&wsm.wait);
	timer_setup(&wsm.timer, zstd_reclaim_timer_fn, 0);

	INIT_LIST_HEAD(&wsm.lru_list);
	for (i = 0; i < ZSTD_BTRFS_MAX_LEVEL; i++)
		INIT_LIST_HEAD(&wsm.idle_ws[i]);

	ws = zstd_alloc_workspace(ZSTD_BTRFS_MAX_LEVEL);
	if (IS_ERR(ws)) {
		pr_warn(
		"BTRFS: cannot preallocate zstd compression workspace\n");
	} else {
		set_bit(ZSTD_BTRFS_MAX_LEVEL - 1, &wsm.active_map);
		list_add(ws, &wsm.idle_ws[ZSTD_BTRFS_MAX_LEVEL - 1]);
	}
}