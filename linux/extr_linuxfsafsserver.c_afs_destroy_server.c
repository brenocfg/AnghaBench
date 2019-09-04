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
struct afs_server {int /*<<< orphan*/  rcu; int /*<<< orphan*/  flags; int /*<<< orphan*/  addresses; } ;
struct afs_net {int dummy; } ;
struct afs_addr_list {size_t index; int /*<<< orphan*/ * addrs; } ;
struct afs_addr_cursor {size_t start; int /*<<< orphan*/  error; int /*<<< orphan*/ * addr; int /*<<< orphan*/  index; struct afs_addr_list* alist; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_MAY_HAVE_CB ; 
 int /*<<< orphan*/  _enter (char*,struct afs_server*) ; 
 int /*<<< orphan*/  afs_dec_servers_outstanding (struct afs_net*) ; 
 int /*<<< orphan*/  afs_fs_give_up_all_callbacks (struct afs_net*,struct afs_server*,struct afs_addr_cursor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_server_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct afs_addr_list* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_destroy_server(struct afs_net *net, struct afs_server *server)
{
	struct afs_addr_list *alist = rcu_access_pointer(server->addresses);
	struct afs_addr_cursor ac = {
		.alist	= alist,
		.start	= alist->index,
		.index	= 0,
		.addr	= &alist->addrs[alist->index],
		.error	= 0,
	};
	_enter("%p", server);

	if (test_bit(AFS_SERVER_FL_MAY_HAVE_CB, &server->flags))
		afs_fs_give_up_all_callbacks(net, server, &ac, NULL);

	call_rcu(&server->rcu, afs_server_rcu);
	afs_dec_servers_outstanding(net);
}