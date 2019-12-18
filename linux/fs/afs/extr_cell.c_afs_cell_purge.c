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
struct afs_net {int /*<<< orphan*/  cells_outstanding; int /*<<< orphan*/  cells_timer; int /*<<< orphan*/  cells_lock; int /*<<< orphan*/  ws_cell; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_put_cell (struct afs_net*,struct afs_cell*) ; 
 int /*<<< orphan*/  afs_queue_cell_manager (struct afs_net*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 struct afs_cell* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

void afs_cell_purge(struct afs_net *net)
{
	struct afs_cell *ws;

	_enter("");

	write_seqlock(&net->cells_lock);
	ws = rcu_access_pointer(net->ws_cell);
	RCU_INIT_POINTER(net->ws_cell, NULL);
	write_sequnlock(&net->cells_lock);
	afs_put_cell(net, ws);

	_debug("del timer");
	if (del_timer_sync(&net->cells_timer))
		atomic_dec(&net->cells_outstanding);

	_debug("kick mgr");
	afs_queue_cell_manager(net);

	_debug("wait");
	wait_var_event(&net->cells_outstanding,
		       !atomic_read(&net->cells_outstanding));
	_leave("");
}