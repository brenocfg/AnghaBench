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
typedef  int /*<<< orphan*/  uuid_t ;
struct afs_server {unsigned long flags; int /*<<< orphan*/  cb_break_lock; int /*<<< orphan*/  cb_volumes; int /*<<< orphan*/  fs_lock; scalar_t__ update_at; int /*<<< orphan*/  uuid; int /*<<< orphan*/  addr_version; int /*<<< orphan*/  addresses; int /*<<< orphan*/  usage; } ;
struct afs_net {int dummy; } ;
struct afs_addr_list {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 unsigned long AFS_SERVER_FL_NEW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct afs_addr_list*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_inc_servers_outstanding (struct afs_net*) ; 
 scalar_t__ afs_server_update_delay ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 struct afs_server* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct afs_server *afs_alloc_server(struct afs_net *net,
					   const uuid_t *uuid,
					   struct afs_addr_list *alist)
{
	struct afs_server *server;

	_enter("");

	server = kzalloc(sizeof(struct afs_server), GFP_KERNEL);
	if (!server)
		goto enomem;

	atomic_set(&server->usage, 1);
	RCU_INIT_POINTER(server->addresses, alist);
	server->addr_version = alist->version;
	server->uuid = *uuid;
	server->flags = (1UL << AFS_SERVER_FL_NEW);
	server->update_at = ktime_get_real_seconds() + afs_server_update_delay;
	rwlock_init(&server->fs_lock);
	INIT_HLIST_HEAD(&server->cb_volumes);
	rwlock_init(&server->cb_break_lock);

	afs_inc_servers_outstanding(net);
	_leave(" = %p", server);
	return server;

enomem:
	_leave(" = NULL [nomem]");
	return NULL;
}