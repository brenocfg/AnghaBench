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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct list_head {int dummy; } ;
struct workspace_manager {int free_ws; TYPE_1__* ops; int /*<<< orphan*/  ws_wait; int /*<<< orphan*/  total_ws; int /*<<< orphan*/  ws_lock; struct list_head idle_ws; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_workspace ) (struct list_head*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (struct list_head*,struct list_head*) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct list_head*) ; 

void btrfs_put_workspace(struct workspace_manager *wsm, struct list_head *ws)
{
	struct list_head *idle_ws;
	spinlock_t *ws_lock;
	atomic_t *total_ws;
	wait_queue_head_t *ws_wait;
	int *free_ws;

	idle_ws	 = &wsm->idle_ws;
	ws_lock	 = &wsm->ws_lock;
	total_ws = &wsm->total_ws;
	ws_wait	 = &wsm->ws_wait;
	free_ws	 = &wsm->free_ws;

	spin_lock(ws_lock);
	if (*free_ws <= num_online_cpus()) {
		list_add(ws, idle_ws);
		(*free_ws)++;
		spin_unlock(ws_lock);
		goto wake;
	}
	spin_unlock(ws_lock);

	wsm->ops->free_workspace(ws);
	atomic_dec(total_ws);
wake:
	cond_wake_up(ws_wait);
}