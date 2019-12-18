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
struct afs_server {int /*<<< orphan*/  rcu; int /*<<< orphan*/  usage; int /*<<< orphan*/  probe_outstanding; int /*<<< orphan*/  flags; int /*<<< orphan*/  addresses; } ;
struct afs_net {int dummy; } ;
struct afs_addr_list {int /*<<< orphan*/  preferred; } ;
struct afs_addr_cursor {int /*<<< orphan*/  error; int /*<<< orphan*/  index; struct afs_addr_list* alist; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_MAY_HAVE_CB ; 
 int /*<<< orphan*/  afs_dec_servers_outstanding (struct afs_net*) ; 
 int /*<<< orphan*/  afs_fs_give_up_all_callbacks (struct afs_net*,struct afs_server*,struct afs_addr_cursor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_server_rcu ; 
 int /*<<< orphan*/  afs_server_trace_destroy ; 
 int /*<<< orphan*/  afs_server_trace_give_up_cb ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct afs_addr_list* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_server (struct afs_server*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void afs_destroy_server(struct afs_net *net, struct afs_server *server)
{
	struct afs_addr_list *alist = rcu_access_pointer(server->addresses);
	struct afs_addr_cursor ac = {
		.alist	= alist,
		.index	= alist->preferred,
		.error	= 0,
	};

	trace_afs_server(server, atomic_read(&server->usage),
			 afs_server_trace_give_up_cb);

	if (test_bit(AFS_SERVER_FL_MAY_HAVE_CB, &server->flags))
		afs_fs_give_up_all_callbacks(net, server, &ac, NULL);

	wait_var_event(&server->probe_outstanding,
		       atomic_read(&server->probe_outstanding) == 0);

	trace_afs_server(server, atomic_read(&server->usage),
			 afs_server_trace_destroy);
	call_rcu(&server->rcu, afs_server_rcu);
	afs_dec_servers_outstanding(net);
}