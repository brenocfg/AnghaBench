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
struct afs_net {int /*<<< orphan*/  servers_outstanding; int /*<<< orphan*/  fs_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_queue_server_manager (struct afs_net*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 

void afs_purge_servers(struct afs_net *net)
{
	_enter("");

	if (del_timer_sync(&net->fs_timer))
		atomic_dec(&net->servers_outstanding);

	afs_queue_server_manager(net);

	_debug("wait");
	wait_var_event(&net->servers_outstanding,
		       !atomic_read(&net->servers_outstanding));
	_leave("");
}